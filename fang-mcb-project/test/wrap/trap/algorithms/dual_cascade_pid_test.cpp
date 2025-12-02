#include "wrap/trap/algorithms/smooth_pid.hpp"
#include "wrap/trap/algorithms/dual_cascade_pid.hpp"
#include <gmock/gmock.h>


namespace trap::algorithms::dualCascadePidTest
{
    using DoubleDualSmoothPid = DualCascadePid<double, double, double, double>;
    using DoubleSmoothPid = SmoothPid<double, double, double>;
    struct MatchTestParam 
    {
        double mainTarget;
        double mainCurrent;
        double intermediateCurrent;
        double deltaTime;
        DoubleDualSmoothPid::Config config;
        double mainErrorDerivative = 0.0;
        double intermediateErrorDerivative = 0.0;
    };

    //Sets up for manually calculating a cascade pid
    //and comparing if DualSmoothPid returns the same results
    //
    class DualCascadePidMatchTest : public testing::TestWithParam<MatchTestParam>
    {
    protected:
        const MatchTestParam& kParam{GetParam()};
        const double kMainTarget{kParam.mainTarget};
        const double kMainCurrent{kParam.mainCurrent};
        const double kIntermediateCurrent{kParam.intermediateCurrent};
        const double kDeltaTime{kParam.deltaTime};
        const DoubleDualSmoothPid::Config kConfig{kParam.config};
        const double kMainErrorDerivative{kParam.mainErrorDerivative};
        const double kIntermediateErrorDerivative{kParam.intermediateErrorDerivative};

        DoubleDualSmoothPid dualPid{kConfig};
        DoubleSmoothPid mainPid{kConfig.mainPidConfig};
        DoubleSmoothPid intermediatePid{kConfig.intermediatePidConfig};

        /**
         * Manually calculate cascading PID
         * 
         * Cascading PID uses one pid to generate the target
         * value for the next pid
         */
        double calculateManualPid()
        {
            const double kMainError{kMainTarget - kMainCurrent};
            const double kIndermediateTarget
            {
                mainPid.runController(kMainError, kDeltaTime)
            };

            // Only cascade through two PIDs
            const double kIntermediateError{kIndermediateTarget - kIntermediateCurrent};
            const double kOutput 
            {
                intermediatePid.runController(kIntermediateError, kDeltaTime)
            };

            return kOutput;
        }
    };


    TEST_P(DualCascadePidMatchTest, generalMatching)
    {
        const double kManualOutput{calculateManualPid()};

        dualPid.setTarget(kMainTarget);
        const double kOutput{
            dualPid.runController(
                kMainCurrent,
                kIntermediateCurrent,
                kDeltaTime
            )
        };

        EXPECT_DOUBLE_EQ(kOutput, kManualOutput);
        // DualSmoothPid needs a means to check the internals
        // Or a means independent of time
    }

    constexpr DoubleDualSmoothPid::IntermediatePid::Config kGeneralPidConfig
    {
        .kp = 1.0,
        .ki = 0.0,
        .kd = 0.0,
        .maxOutput = 10000
    };

    constexpr DoubleDualSmoothPid::Config kConfig
    {
        .mainPidConfig = kGeneralPidConfig,
        .intermediatePidConfig = kGeneralPidConfig,
        .mainPidInitialValue = 0.0,
        .intermediatePidInitialValue = 0.0
    };

    INSTANTIATE_TEST_CASE_P
    (
        zero,
        DualCascadePidMatchTest,
        ::testing::Values
        (
            MatchTestParam
            {
                .mainTarget = 0.0,
                .mainCurrent = 0.0,
                .intermediateCurrent = 0.0,
                .deltaTime = 1.0, // Delta time cannot be zero
                .config = kConfig,
                .mainErrorDerivative = 0.0,
                .intermediateErrorDerivative = 0.0
            }
        )
    );

    // Example of multiple values
    INSTANTIATE_TEST_CASE_P
    (
        positive,
        DualCascadePidMatchTest,
        ::testing::Values
        (
            MatchTestParam
            {
                .mainTarget = 324.230,
                .mainCurrent = 23.0,
                .intermediateCurrent = 232.0,
                .deltaTime = 1.0, // Delta time cannot be zero
                .config = kConfig,
                .mainErrorDerivative = 0.0,
                .intermediateErrorDerivative = 0.0
            },
            MatchTestParam
            {
                .mainTarget = 10.0,
                .mainCurrent = 1.0,
                .intermediateCurrent = 1.0,
                .deltaTime = 1.0, // Delta time cannot be zero
                .config = kConfig,
                .mainErrorDerivative = 0.0,
                .intermediateErrorDerivative = 0.0
            },
            MatchTestParam
            {
                .mainTarget = 1.0,
                .mainCurrent = 3.0,
                .intermediateCurrent = 0.0,
                .deltaTime = 1.0, // Delta time cannot be zero
                .config = kConfig,
                .mainErrorDerivative = 0.0,
                .intermediateErrorDerivative = 0.0
            }
        )
    );

    // TODO: Add more test cases

    TEST(dualSmoothPid, compilationTest)
    {
        constexpr DoubleDualSmoothPid::IntermediatePid::Config kGeneralPidConfig
        {
            .kp = 1.0,
            .ki = 23.3,
            .kd = 14.0
        };

        constexpr DoubleDualSmoothPid::Config kConfig
        {
            .mainPidConfig = kGeneralPidConfig,
            .intermediatePidConfig = kGeneralPidConfig,
            .mainPidInitialValue = 0.0,
            .intermediatePidInitialValue = 0.0
        };

        DoubleDualSmoothPid pid{kConfig};
    }
}