#include "driver/motor/pid/dual_cascade_motor/dual_cascade_motor.hpp"
#include "wrap/trap/algorithms/dual_cascade_pid.hpp"

#include "rail/mock/telemetry/itelemetry_mock.hpp"

#include <memory>
#include <gtest/gtest.h>

namespace fang::motor::dualCascadeMotorTest
{
    using DoubleDualSmoothPid = trap::algorithms::DualCascadePid<double, double, double, double>;
    using TelemetryMock = rail::telemetry::ITelemetryMock<double>;

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

    TEST(dualCascadeMotor, zero)
    {
        // Basic match test
        // The output of the motor should be the same as a dualCascadePid
        // fed the same data

        // Connect the motor to two telemetry mock objects
        // Connect the motor to OutputMotorMock
    }

    // Update test

    // Initialize test
}