#pragma once

#include "robot/variant/pierce/custom_variant/subsystem/pierce_field_gimbal.hpp"

namespace fang::robot::pierceAuto
{
    using namespace units::literals;
    static const trap::motor::DjiSpeedPid::Config kPitchPidConfig
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
    static const trap::motor::DjiGM6020::Config kPitchMotorConfig
    {
        tap::motor::MOTOR2,
        tap::can::CanBus::CAN_BUS1,
        "pitchMotor",
        true,
        1.0,
        kPitchPidConfig,
        false
    };

    static const trap::motor::DjiSpeedPid::Config kYawPidConfig
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
    static const trap::motor::DjiGM6020::Config kYawMotorConfig 
    {
        tap::motor::MOTOR1,
        tap::can::CanBus::CAN_BUS1,
        "yawMotor",
        false,
        1.0,
        kYawPidConfig,
        false
    };

    turret::BasicFieldPitchSystem::Config kBasicFieldPitchConfig
    {
        .pitchError = 0_deg,
        .pitchRange = {-25_deg, 10_deg}
    };

    static const turret::PierceFieldGimbal::PitchSystem::Config kPitchSystemConfig
    {
        .motorConfig = kPitchMotorConfig,
        .pitchSystemConfig = kBasicFieldPitchConfig
    };

    turret::PierceFieldGimbal::YawSystem::Config kYawSystemConfig 
    {
        .motorConfig = kYawMotorConfig,
        .yawError = -7.5_deg
    };

    static const turret::PierceFieldGimbal::Config kGimbalSubsystemConfig
    {
        .pitchSystemConfig = kPitchSystemConfig,
        .yawSystemConfig = kYawSystemConfig
    };
}