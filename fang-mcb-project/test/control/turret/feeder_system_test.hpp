#ifndef FANG_ROBOTICS_MCB_TEST_FLYWHEEL_SYSTEM_TEST_HPP
#define FANG_ROBOTICS_MCB_TEST_FLYWHEEL_SYSTEM_TEST_HPP
#include "control/turret/feeder_system.hpp"

#include "unitaliases.hpp"
#include "drivers.hpp"

#include <gtest/gtest.h>
#include <tuple>


namespace test
{
    class FeederSystemTest: public ::testing::TestWithParam<std::tuple<int, Hertz,RPM>>
    {
    public:

        const int roundsPerRevolution{std::get<0>(GetParam())};
        const Meters feedRate{std::get<1>(GetParam())};
        const MetersPerSecond expectedRPMCall{std::get<1>(GetParam())};

        Drivers drivers;
        const control::turret::FeederSystem::DriveMotor::DjiSpeedPid::Config defaultConfig 
        {
            1,
            1,
            1
        };
        const control::turret::FeederSystem::DriveMotor::Config motorConfig
        {
            tap::motor::MOTOR1,
            tap::can::CanBus::CAN_BUS1,
            "test motor",
            false,
            1.0,
            defaultConfig
        };
        const control::turret::FeederSystem::Config feederConfig{roundsPerRevolution, feedRate, motorConfig};

        control::turret::FeederSystem feederSystem{drivers, flywheelConfig};
        control::turret::FeederSystem::DriveMotor& motor{feederSystem.m_motor};
    };
}
#endif