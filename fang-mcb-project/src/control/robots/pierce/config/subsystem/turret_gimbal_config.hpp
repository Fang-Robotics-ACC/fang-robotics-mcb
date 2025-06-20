#ifndef FANG_ROBOTICS_MCB_PIERCE_TURRET_GIMBAL_CONFIG_HPP
#define FANG_ROBOTICS_MCB_PIERCE_TURRET_GIMBAL_CONFIG_HPP
#include "control/turret/gimbal_subsystem.hpp"

namespace control
{
    using namespace units::literals;
    static const trap::motor::DjiSpeedPid::Config k_pitchPidConfig
    {
        70000,
        0.1,
        10000,
        3000,
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
        0.2,
        50'000,
        7000,
        trap::motor::DjiGM6020::k_maxOutput
    };
    static const trap::motor::DjiGM6020::Config k_yawConfig
    {
        tap::motor::MOTOR1,
        tap::can::CanBus::CAN_BUS1,
        "yawMotor",
        false,
        1.0,
        k_yawPidConfig,
        false
    };

    using GimbalSystem = control::turret::GimbalSystem;
    static const GimbalSystem::Config k_gimbalConfig
    {
        -25_deg,
        30_deg,
        k_pitchMotorConfig,
        k_yawConfig
    };

    static const turret::GimbalSubsystem::Config k_gimbalSubsystemConfig
    {
        7_deg,
        k_gimbalConfig,
    };
}
#endif