#pragma once

#include "robot/variant/pierce/custom_variant/subsystem/pierce_field_gimbal.hpp"

namespace fang::robot 
{
    using namespace units::literals;
    static const trap::motor::DjiSpeedPid::Config kPitchPositionPid
    {
        .kp                 = 0,
        .ki                 = 0,
        .kd                 = 0.0,
        .maxICumulative     = 0,
        .maxOutput          = trap::motor::DjiGM6020::kMaxOutput,
        .tQDerivativeKalman = 0.01, //Cause value to be more "sluggish to reduce oscillation"
        .tRDerivativeKalman = 0.0,
        .errorDerivativeFloor = 0.0 //radians
    };

    static const trap::motor::DjiSpeedPid::Config kPitchVelocityPid
    {
        .kp                 = 0,
        .ki                 = 0,
        .kd                 = 0.0,
        .maxICumulative     = 0,
        .maxOutput          = trap::motor::DjiGM6020::kMaxOutput,
        .tQDerivativeKalman = 0.0, //Cause value to be more "sluggish to reduce oscillation"
        .tRDerivativeKalman = 0.0,
        .errorDerivativeFloor = 0.0 //radians
    };

    static const trap::motor::DjiGM6020::Config kPitchMotorConfig
    {
        .motorId    = tap::motor::MOTOR2,
        .canBus     = tap::can::CanBus::CAN_BUS1,
        .name       = "pitchMotor",
        .inverted   =  true,
        .currentControl = false
    };

    static const motor::DualCascadeGm6020::PidMotor::Config kPitchMotorPidConfig
    {
        .mainPidConfig = kPitchPositionPid,
        .intermediatePidConfig = kPitchVelocityPid,
        .mainPidInitialValue = 0.0_rad,
        .intermediatePidInitialValue = 0.0_rpm,
    };

    static const motor::DualCascadeGm6020::Config kDualCascadePitchMotorConfig
    {
        .motorConfig = kPitchMotorConfig,
        .pidMotorConfig = kPitchMotorPidConfig
    };

    static const trap::motor::DjiSpeedPid::Config kYawPositionPid
    {
        .kp                 = 0,
        .ki                 = 0,
        .kd                 = 0.0,
        .maxICumulative     = 0,
        .maxOutput          = trap::motor::DjiGM6020::kMaxOutput,
        .tQDerivativeKalman = 0.01, //Cause value to be more "sluggish to reduce oscillation"
        .tRDerivativeKalman = 0.0,
        .errorDerivativeFloor = 0.0 //radians
    };

    static const trap::motor::DjiSpeedPid::Config kYawVelocityPid
    {
        .kp                 = 0,
        .ki                 = 0,
        .kd                 = 0.0,
        .maxICumulative     = 0,
        .maxOutput          = trap::motor::DjiGM6020::kMaxOutput,
        .tQDerivativeKalman = 0.0, //Cause value to be more "sluggish to reduce oscillation"
        .tRDerivativeKalman = 0.0,
        .errorDerivativeFloor = 0.0 //radians
    };

    static const motor::DualCascadeGm6020::PidMotor::Config kYawMotorPidConfig
    {

        .mainPidConfig = kYawPositionPid,
        .intermediatePidConfig = kYawVelocityPid,
        .mainPidInitialValue = 0.0_rad,
        .intermediatePidInitialValue = 0.0_rpm,
    };

    static const trap::motor::DjiGM6020::Config kYawMotorConfig 
    {
        .motorId    = tap::motor::MOTOR1,
        .canBus     = tap::can::CanBus::CAN_BUS1,
        .name       = "yawMotor",
        .inverted   = false,
        .currentControl = false
    };

    static const motor::DualCascadeGm6020::Config kDualCascadeYawMotorConfig
    {
        .motorConfig = kYawMotorConfig,
        .pidMotorConfig = kYawMotorPidConfig 
    };

    static const turret::BasicFieldPitchSystem::Config kBasicFieldPitchConfig
    {
        .pitchError = 0_deg,
        .pitchRange = {-25_deg, 10_deg}
    };

    static const turret::PierceFieldGimbal::PitchSystem::Config kPitchSystemConfig
    {
        .motorConfig = kDualCascadePitchMotorConfig,
        .pitchSystemConfig = kBasicFieldPitchConfig
    };

    static turret::PierceFieldGimbal::YawSystem::Config kYawSystemConfig 
    {
        .motorConfig = kDualCascadeYawMotorConfig,
        .yawSystemConfig = turret::PierceFieldGimbal::YawSystem::ChassisFieldYawSystem::Config
        {
            .yawError =-7.5_deg
        }
    };

    static const turret::PierceFieldGimbal::Config kGimbalSubsystemConfig
    {
        .pitchSystemConfig = kPitchSystemConfig,
        .yawSystemConfig = kYawSystemConfig
    };
}