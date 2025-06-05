#ifndef FANG_ROBOTICS_MCB_TEST_FLYWHEEL_SYSTEM_TEST_HPP
#define FANG_ROBOTICS_MCB_TEST_FLYWHEEL_SYSTEM_TEST_HPP
#include "control/turret/flywheel_system.hpp"

#include "unitaliases.hpp"
#include "drivers.hpp"

#include <gtest/gtest.h>
#include <tuple>


namespace test
{
    class FlywheelSpeedTest : public ::testing::TestWithParam<std::tuple<Meters, MetersPerSecond,RPM>>
    {
    public:
        const Meters radius{std::get<0>(GetParam())};
        const MetersPerSecond targetRimSpeed{std::get<1>(GetParam())};
        const RPM expectedRPMCall{std::get<2>(GetParam())};


        Drivers drivers;
        const control::turret::FlywheelSystem::DriveMotor::DjiSpeedPid::Config defaultConfig 
        {
            1,
            1,
            1
        };
        const control::turret::FlywheelSystem::DriveMotor::Config motorConfig
        {
            tap::motor::MOTOR1,
            tap::can::CanBus::CAN_BUS1,
            "test motor",
            false,
            1.0,
            defaultConfig
        };
        const control::turret::FlywheelSystem::Config flywheelConfig{radius, motorConfig};

        control::turret::FlywheelSystem flywheelSystem{drivers, flywheelConfig};
        control::turret::FlywheelSystem::DriveMotor& motor{flywheelSystem.m_motor};
    };
}
#endif