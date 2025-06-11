#ifndef FANG_ROBOTICS_MCB_PIERCE_TURRET_CONFIG_HPP
#define FANG_ROBOTICS_MCB_PIERCE_TURRET_CONFIG_HPP
#include "control/turret/gimbal_system.hpp"
#include "control/turret/turret_subsystem.hpp"
#include "unitaliases.hpp"
namespace control
{
    using namespace units::literals;
    static const trap::motor::DjiSpeedPid::Config k_pitchPidConfig
    {
        50000,
        1000,
        20,
        100,
        trap::motor::DjiGM6020::k_maxOutput
    };
    static const trap::motor::DjiGM6020::Config k_pitchMotorConfig
    {
        tap::motor::MOTOR2,
        tap::can::CanBus::CAN_BUS1,
        "pitchMotor",
        true,
        1.0,
        k_pitchPidConfig,
        false
    };

    static const trap::motor::DjiSpeedPid::Config k_yawPidConfig
    {
        50000,
        1000,
        0,
        100,
        trap::motor::DjiGM6020::k_maxOutput
    };
    static const trap::motor::DjiGM6020::Config k_yawConfig
    {
        tap::motor::MOTOR1,
        tap::can::CanBus::CAN_BUS1,
        "yawMotor",
        true,
        1.0,
        k_yawPidConfig,
        false
    };

    using GimbalSystem = control::turret::GimbalSystem;
    static const GimbalSystem::Config k_gimbalConfig
    {
        -10_deg,
        10_deg,
        k_pitchMotorConfig,
        k_yawConfig
    };

    static const control::turret::TurretSubsystem::Config k_turretConfig
    {
        k_gimbalConfig
    };


};
#endif