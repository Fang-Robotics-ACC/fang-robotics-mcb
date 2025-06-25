#ifndef FANG_ROBOTICS_MCB_PIERCE_TURRET_GIMBAL_CONFIG_HPP
#define FANG_ROBOTICS_MCB_PIERCE_TURRET_GIMBAL_CONFIG_HPP
#include "control/turret/gimbal_subsystem.hpp"

namespace control
{
    using namespace units::literals;
    static const trap::motor::DjiSpeedPid::Config k_pitchPidConfig
    {
        .kp                 = 200'000,
        .ki                 = 5,
        .kd                 = 000.0,
        .maxICumulative     = 7000,
        .maxOutput          = trap::motor::DjiGM6020::k_maxOutput,
        .tQDerivativeKalman = 0.01, //Cause value to be more "sluggish to reduce oscillation"
        .tRDerivativeKalman = 1000.0,
        .errorDerivativeFloor = 0.1 //radians
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
        .kp                 = 100'000,
        .ki                 = 5,
        .kd                 = 2500.0,
        .maxICumulative     = 7000,
        .maxOutput          = trap::motor::DjiGM6020::k_maxOutput,
        .tQDerivativeKalman = 0.01, //Cause value to be more "sluggish to reduce oscillation"
        .tRDerivativeKalman = 1000.0,
        .errorDerivativeFloor = 0.10 //radians
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
        .homeYawOffset  = -7.75_deg,
        .gimbalConfig   = k_gimbalConfig,
    };
}
#endif