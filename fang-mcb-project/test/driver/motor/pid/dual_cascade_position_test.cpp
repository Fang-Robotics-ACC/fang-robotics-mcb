#include "driver/motor/pid/dual_cascade_position/dual_cascade_position.hpp"

#include "rail/mock/telemetry/itelemetry_mock.hpp"
#include "rail/mock/motor/ioutput_motor_mock.hpp"

#include "wrap/units/units_alias.hpp"

#include <memory>
#include <gtest/gtest.h>

namespace fang::motor::dualCascadePositionTest
{
    using DoubleDualSmoothPid = trap::algorithms::DualCascadePid<double, double, double, double>;
    using TelemetryMock = rail::telemetry::ITelemetryMock<double>;
    using OutputMotorMock = rail::motor::IOutputMotorMock<double>;

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

    TEST(dualCascadeMotor, compilation)
    {
        std::unique_ptr<OutputMotorMock> motor{std::make_unique<OutputMotorMock>()};
        auto positionTelemetry{
            std::make_unique<rail::telemetry::ITelemetryMock<trap::algorithms::RingRadians>>()
        };
        std::unique_ptr<TelemetryMock> speedTelemetry{std::make_unique<TelemetryMock>()};

        DualCascadePosition<double, double> cascadeMotor
        {
            DualCascadePosition<double, double>::Config{},
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

    //TODO:
    // Basic match test
    // The output of the motor should be the same as a dualCascadePid
    // fed the same data

    // Connect the motor to two telemetry mock objects
    // Connect the motor to OutputMotorMock
}