#include "driver/motor/pid/dual_cascade_motor/dual_cascade_motor.hpp"

#include "rail/mock/telemetry/itelemetry_mock.hpp"

#include <gtest/gtest.h>

namespace fang::motor::dualCascadeMotorTest
{
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