#include "wrap/trap/motor/dji_motor_aliases.hpp"
#include "wrap/trap/algorithms/dual_cascade_pid.hpp"
#include "wrap/trap/algorithms/ring_radians.hpp"
#include "wrap/trap/algorithms/smooth_pid.hpp"

#include "wrap/units/units_alias.hpp"

#include <gmock/gmock.h>

namespace trap::algorithms::dualCascadePidRingTest
{
    using namespace units::literals;
    using CascadePid = DualCascadePid<RingRadians, RPM, motor::DjiMotorOutput, Seconds>;
    using DoubleSmoothPid = SmoothPid<double, double, double>;
    struct MatchTestParam 
    {
        Radians mainTarget;
        Radians mainCurrent;
        RPM intermediateCurrent;
        Seconds deltaTime;
        CascadePid::Config config;
    };

    //Sets up for manually calculating a cascade pid
    //and comparing if DualSmoothPid returns the same results
    //
    class DualCascadePidMatchRingTest : public testing::TestWithParam<MatchTestParam>
    {
    protected:
        const MatchTestParam& kParam{GetParam()};
        const Radians kMainTarget{kParam.mainTarget};
        const Radians kMainCurrent{kParam.mainCurrent};
        const RPM kIntermediateCurrent{kParam.intermediateCurrent};
        const Seconds kDeltaTime{kParam.deltaTime};
        const CascadePid::Config kConfig{kParam.config};

        CascadePid dualPid{kConfig};
        CascadePid::MainPid mainPid{kConfig.mainPidConfig};
        CascadePid::IntermediatePid intermediatePid{kConfig.intermediatePidConfig};

        /**
         * Manually calculate cascading PID
         * 
         * Cascading PID uses one pid to generate the target
         * value for the next pid
         */
        double calculateManualPid()
        {
            const Radians kMainError{RingRadians{kMainTarget} - RingRadians{kMainCurrent}};
            const RPM kIndermediateTarget{
                mainPid.runController(kMainError, kDeltaTime)
            };

            // Only cascade through two PIDs
            const RPM kIntermediateError{kIndermediateTarget - kIntermediateCurrent};
            const motor::DjiMotorOutput kOutput {
                intermediatePid.runController(kIntermediateError, kDeltaTime)
            };

            return kOutput;
        }
    };


    TEST_P(DualCascadePidMatchRingTest, generalMatching)
    {
        const double kManualOutput{calculateManualPid()};

        dualPid.setTarget(kMainTarget);
        const double kOutput{
            dualPid.runController(
                kMainCurrent,
                kIntermediateCurrent
            )
        };

        EXPECT_DOUBLE_EQ(kOutput, kManualOutput);
        // DualSmoothPid needs a means to check the internals
        // Or a means independent of time
    }

    const CascadePid::IntermediatePid::Config kGeneralPidConfig
    {
        .kp = 1.0,
        .ki = 12.0,
        .kd = 4.0,
        .maxOutput = 10000
    };

    const CascadePid::Config kConfig
    {
        .mainPidConfig = kGeneralPidConfig,
        .intermediatePidConfig = kGeneralPidConfig,
        .mainPidInitialValue = {0.0_rad},
        .intermediatePidInitialValue = 0.0_rpm
    };

    INSTANTIATE_TEST_CASE_P
    (
        zero,
        DualCascadePidMatchRingTest,
        ::testing::Values
        (
            MatchTestParam
            {
                .mainTarget = 0.0_rad,
                .mainCurrent = 0.0_rad,
                .intermediateCurrent = 0.0_rpm,
                .deltaTime = 1.0_s, // Delta time cannot be zero
                .config = kConfig
            }
        )
    );

    // Example of multiple values
    INSTANTIATE_TEST_CASE_P
    (
        positive,
        DualCascadePidMatchRingTest,
        ::testing::Values
        (
            MatchTestParam{
                .mainTarget = 324.230_rad,
                .mainCurrent = 23.0_rad,
                .intermediateCurrent = 232.0_rpm,
                .deltaTime = 1.0_s, // Delta time cannot be zero
                .config = kConfig
            },
            MatchTestParam{
                .mainTarget = 10.0_rad,
                .mainCurrent = 1.0_rad,
                .intermediateCurrent = 1.0_rpm,
                .deltaTime = 1.0_s, // Delta time cannot be zero
                .config = kConfig
            },
            MatchTestParam{
                .mainTarget = 1.0_rad,
                .mainCurrent = 3.0_rad,
                .intermediateCurrent = 0.0_rpm,
                .deltaTime = 1.0_s, // Delta time cannot be zero
                .config = kConfig
            }
        )
    );

    // TODO: Add more test cases

    TEST(dualSmoothPid, compilationTest)
    {
        constexpr CascadePid::IntermediatePid::Config kGeneralPidConfig
        {
            .kp = 1.0,
            .ki = 23.3,
            .kd = 14.0
        };

        const CascadePid::Config kConfig
        {
            .mainPidConfig = kGeneralPidConfig,
            .intermediatePidConfig = kGeneralPidConfig,
            .mainPidInitialValue = {0.0_rad},
            .intermediatePidInitialValue = 0.0_rpm
        };

        CascadePid pid{kConfig};
    }
}