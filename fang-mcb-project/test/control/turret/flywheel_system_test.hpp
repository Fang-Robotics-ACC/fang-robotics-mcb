#ifndef FANG_ROBOTICS_MCB_TEST_FLYWHEEL_SYSTEM_TEST_HPP
#define FANG_ROBOTICS_MCB_TEST_FLYWHEEL_SYSTEM_TEST_HPP

#include "unitaliases.hpp"
#include "drivers.hpp"

#include <gtest/gtest.h>
#include <tuple>

#include "control/turret/systems/flywheel_system.hpp"
namespace control::turret
{
    class FlywheelSystem;
}

namespace test
{
    class FlywheelSpeedTest : public ::testing::TestWithParam<std::tuple<Meters, MetersPerSecond,RPM>>
    {
    public:
    using FlywheelSystem = control::turret::FlywheelSystem;
        const Meters radius{std::get<0>(GetParam())};
        const MetersPerSecond targetRimSpeed{std::get<1>(GetParam())};
        const RPM expectedRPMCall{std::get<2>(GetParam())};


        Drivers drivers;
        const FlywheelSystem::DriveMotor::DjiSpeedPid::Config defaultConfig 
        {
            1,
            1,
            1
        };
        const FlywheelSystem::DriveMotor::Config motorConfig
        {
            tap::motor::MOTOR1,
            tap::can::CanBus::CAN_BUS1,
            "test motor",
            false,
            1.0,
            defaultConfig
        };
        const FlywheelSystem::Config flywheelConfig{radius, motorConfig};

        FlywheelSystem flywheelSystem{drivers, flywheelConfig};
        FlywheelSystem::DriveMotor& motor{flywheelSystem.m_motor};
    };
}
#endif