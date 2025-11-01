#include "driver/motor/pid/dual_cascade_motor/dual_cascade_motor.hpp"
#include "wrap/trap/algorithms/dual_cascade_pid.hpp"

#include "rail/mock/telemetry/itelemetry_mock.hpp"
#include "rail/mock/motor/ioutput_motor_mock.hpp"

#include <memory>
#include <gtest/gtest.h>

namespace fang::motor::dualCascadeMotorTest
{
    using namespace units::literals;
    using DoubleDualSmoothPid = trap::algorithms::DualCascadePid<double, double, double, Seconds>;
    using TelemetryMock = rail::telemetry::ITelemetryMock<double>;
    using OutputMotorMock = rail::motor::IOutputMotorMock<double>;

    struct MatchTestParam 
    {
        double mainTarget;
        double mainCurrent;
        double intermediateCurrent;
        Seconds deltaTime;
        DoubleDualSmoothPid::Config config;
    };

    class DualCascadeMotorMatchTest : public testing::TestWithParam<MatchTestParam>
    {
    protected:
        const MatchTestParam kParam{GetParam()};
        DoubleDualSmoothPid dualPid{kParam.config};
        std::unique_ptr<OutputMotorMock> outputMotorMock{std::make_unique<OutputMotorMock>()};
        std::unique_ptr<TelemetryMock> positionTelemetry{std::make_unique<TelemetryMock>()};
        std::unique_ptr<TelemetryMock> speedTelemetry{std::make_unique<TelemetryMock>()};

        OutputMotorMock* outputMotorPtr{outputMotorMock.get()};
        TelemetryMock* positionTelemetryPtr{positionTelemetry.get()};
        TelemetryMock* speedTelemetryPtr{speedTelemetry.get()};

        DualCascadeMotor<double, double, double> cascadeMotor{
            kParam.config,
            std::move(outputMotorMock),
            std::move(positionTelemetry),
            std::move(speedTelemetry)
        };
    };

    /**
     * WARNING: THIS UTILIZED A BACKDOOR FUNCTION
     * THE SELF-DELTA FUNCTION IS NOT CALLED AT ALL
     * 
     * Assert that the motor is setting things the correct way
     * (delegating telemetry and dual cascade pid properly)
     */
    TEST_P(DualCascadeMotorMatchTest, matchTest)
    {
        ON_CALL(*positionTelemetryPtr, getData())
            .WillByDefault(testing::Return(kParam.mainCurrent));

        ON_CALL(*speedTelemetryPtr, getData())
            .WillByDefault(testing::Return(kParam.intermediateCurrent));

        cascadeMotor.setTarget(kParam.mainTarget);

        dualPid.setTarget(kParam.mainTarget);

        const double kExpectedOutput{
            dualPid.runController(
                kParam.mainCurrent,
                kParam.intermediateCurrent,
                kParam.deltaTime
            )
        };
    
        EXPECT_CALL(*outputMotorPtr, setTargetOutput(kExpectedOutput));

        cascadeMotor.update(kParam.deltaTime);
    }

    const DoubleDualSmoothPid::IntermediatePid::Config kGeneralPidConfig
    {
        .kp = 1.0,
        .ki = 12.0,
        .kd = 4.0,
        .maxOutput = 10000
    };

    const DoubleDualSmoothPid::Config kConfig
    {
        .mainPidConfig = kGeneralPidConfig,
        .intermediatePidConfig = kGeneralPidConfig,
        .mainPidInitialValue = 0.0,
        .intermediatePidInitialValue = 0.0
    };

    INSTANTIATE_TEST_CASE_P
    (
        zero,
        DualCascadeMotorMatchTest,
        testing::Values
        (
            MatchTestParam 
            {
                .mainTarget = 0.0,
                .mainCurrent = 0.0,
                .intermediateCurrent = 0.0,
                .deltaTime = 1.0_s, // Delta time equal to zero leads to NAN error
                .config = kConfig
            }
        )
    );

    INSTANTIATE_TEST_CASE_P
    (
        positive,
        DualCascadeMotorMatchTest,
        testing::Values
        (
            MatchTestParam 
            {
                .mainTarget = 100.0,
                .mainCurrent = 10.0,
                .intermediateCurrent = 10.0,
                .deltaTime = 1.0_s, // Delta time equal to zero leads to NAN error
                .config = kConfig
            },
            MatchTestParam 
            {
                .mainTarget = 12323.0,
                .mainCurrent = 134.0,
                .intermediateCurrent = 13290.0,
                .deltaTime = 1.0_s, // Delta time equal to zero leads to NAN error
                .config = kConfig
            },
            MatchTestParam 
            {
                .mainTarget = 120.0,
                .mainCurrent = 354.0,
                .intermediateCurrent = 458.0,
                .deltaTime = 0.23_s, // Delta time equal to zero leads to NAN error
                .config = kConfig
            }
        )
    );


    TEST(dualCascadeMotor, compilation)
    {
        std::unique_ptr<OutputMotorMock> motor{std::make_unique<OutputMotorMock>()};
        std::unique_ptr<TelemetryMock> positionTelemetry{std::make_unique<TelemetryMock>()};
        std::unique_ptr<TelemetryMock> speedTelemetry{std::make_unique<TelemetryMock>()};
        DualCascadeMotor<double, double, double> cascadeMotor 
        {
            DualCascadeMotor<double, double, double>::Config{},
            std::move(motor),
            std::move(positionTelemetry),
            std::move(speedTelemetry)
        };
    }

    TEST(dualCascadeMotor, initializeAndUpdate)
    {
        std::unique_ptr<OutputMotorMock> motor{std::make_unique<OutputMotorMock>()};
        std::unique_ptr<TelemetryMock> positionTelemetry{std::make_unique<TelemetryMock>()};
        std::unique_ptr<TelemetryMock> speedTelemetry{std::make_unique<TelemetryMock>()};

        OutputMotorMock* motorPtr{motor.get()};

        DualCascadeMotor<double, double, double> cascadeMotor 
        {
            DualCascadeMotor<double, double, double>::Config{},
            std::move(motor),
            std::move(positionTelemetry),
            std::move(speedTelemetry)
        };

        EXPECT_CALL(*motorPtr, initialize());
        EXPECT_CALL(*motorPtr, update());

        cascadeMotor.initialize();
        cascadeMotor.update();
    }
    // TODO: Use non-backdoor match testing
}