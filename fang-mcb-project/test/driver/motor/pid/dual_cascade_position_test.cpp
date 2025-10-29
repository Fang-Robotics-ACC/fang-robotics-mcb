#include "driver/motor/pid/dual_cascade_position/dual_cascade_position.hpp"

#include "rail/mock/telemetry/itelemetry_mock.hpp"
#include "rail/mock/motor/ioutput_motor_mock.hpp"

#include "wrap/units/units_alias.hpp"

#include <memory>
#include <gtest/gtest.h>

namespace fang::motor::dualCascadePositionTest
{
    using PositionCascadeMotor = DualCascadePosition<double, RPM>;
    using DualPid = PositionCascadeMotor::Pid;

    using MainTelemetry= rail::telemetry::ITelemetryMock<trap::algorithms::RingRadians>;
    using IntermediateTelemetry= rail::telemetry::ITelemetryMock<RPM>;
    using OutputMotorMock = rail::motor::IOutputMotorMock<double>;
    using TelemetryMock = rail::telemetry::ITelemetryMock<double>;

    using namespace units::literals;

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

    class DualCascadeMotorMatchTest : public testing::TestWithParam<MatchTestParam>
    {
    protected:
        const MatchTestParam kParam{GetParam()};
        DoubleDualSmoothPid dualPid{kParam.config};
        std::unique_ptr<TelemetryMock> positionTelemetry{std::make_unique<TelemetryMock>()};
        std::unique_ptr<TelemetryMock> speedTelemetry{std::make_unique<TelemetryMock>()};

        /*
        DualCascadeMotor<double, double, double> cascadeMotor
        {


        };
        */
    };

    TEST_P(DualCascadePositionMatchTest, matchTest)
    {
        ON_CALL(positionTelemetry, getData())
            .WillByDefault(testing::Return(kParam.mainCurrent));

        ON_CALL(speedTelemetry, getData())
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
    
        EXPECT_CALL(outputMotor, setTargetOutput(kExpectedOutput));

        cascadeMotor.update(kParam.deltaTime);
    }

    const DualPid::MainPid::Config kMainDefaultPidConfig{
        .kp = 1.0,
        .ki = 12.0,
        .kd = 4.0,
        .maxOutput = 10000
    };

    const DualPid::IntermediatePid::Config kIntermediateDefaultPidConfig{
        .kp = 1.0,
        .ki = 12.0,
        .kd = 4.0,
        .maxOutput = 10000
    };

    const DualPid::Config kConfig{
        .mainPidConfig = kMainDefaultPidConfig,
        .intermediatePidConfig = kIntermediateDefaultPidConfig,
        .mainPidInitialValue = 0.0_rad,
        .intermediatePidInitialValue = 0.0_rpm
    };

    INSTANTIATE_TEST_CASE_P
    (
        zero,
        DualCascadePositionMatchTest,
        testing::Values
        (
            MatchTestParam 
            {
                .mainTarget = 0.0_rad,
                .mainCurrent = 0.0_rad,
                .intermediateCurrent = 0.0_rpm,
                .deltaTime = 1.0_s, // Delta time equal to zero leads to NAN error
                .config = kConfig 
            }
        )
    );

    INSTANTIATE_TEST_CASE_P
    (
        positive,
        DualCascadePositionMatchTest,
        testing::Values
        (
            MatchTestParam 
            {
                .mainTarget = 1.0_rad,
                .mainCurrent = 3.0_rad,
                .intermediateCurrent = 0_rpm,
                .deltaTime = 1.0_s, // Delta time equal to zero leads to NAN error
                .config = kConfig 
            },
            MatchTestParam 
            {
                .mainTarget = 3.0_rad,
                .mainCurrent = 1.0_rad,
                .intermediateCurrent = 100_rpm,
                .deltaTime = 1.0_s, // Delta time equal to zero leads to NAN error
                .config = kConfig 
            }
        )
    );

    TEST(dualCascadeMotor, compilation)
    {
        std::unique_ptr<OutputMotorMock> motor{std::make_unique<OutputMotorMock>()};

        auto positionTelemetry{
            std::make_unique<rail::telemetry::ITelemetryMock<trap::algorithms::RingRadians>>()
        };

        std::unique_ptr<IntermediateTelemetry> speedTelemetry{std::make_unique<IntermediateTelemetry>()};

        DualCascadePosition<double, RPM> cascadeMotor
        {
            DualCascadePosition<double, RPM>::Config{},
            std::move(motor),
            std::move(positionTelemetry),
            std::move(speedTelemetry)
        };
    }

    //TODO:
    // Basic match test
    // The output of the motor should be the same as a dualCascadePid
    // fed the same data

    // Connect the motor to two telemetry mock objects
    // Connect the motor to OutputMotorMock
}