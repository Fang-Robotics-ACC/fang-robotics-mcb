#pragma once

#include "robot/variant/pierce/custom_variant/subsystem/pierce_field_gimbal.hpp"

namespace fang::robot 
{
inline const turret::PierceFieldGimbal::Config& getPierceGimbalConfig()
{
    using namespace units::literals;
    
    static const trap::motor::DjiSpeedPid::Config kPitchPositionPid
    {
        .kp                 = 50.0,
        .ki                 = 0.0,
        .kd                 = 0.0,
        .maxICumulative     = 0.0,
        .maxOutput          = trap::motor::DjiGM6020::kMaxOutput,
        .tQDerivativeKalman = 1.0, //Cause value to be more "sluggish to reduce oscillation"
        .tRDerivativeKalman = 0.0,
        .tQProportionalKalman = 1.0,
        .tRProportionalKalman = 500.0,
        .errDeadzone = 0.17
    };

    static const trap::motor::DjiSpeedPid::Config kPitchVelocityPid
    {
        .kp                 = 5'000,
        .ki                 = 0,
        .kd                 = 0.0,
        .maxICumulative     = 0,
        .maxOutput          = trap::motor::DjiGM6020::kMaxOutput,
        .tQDerivativeKalman = 1.0, //Cause value to be more "sluggish to reduce oscillation"
        .tRDerivativeKalman = 0.0,
        .tQProportionalKalman = 1,
        .tRProportionalKalman = 150'000.0,
    };

    static const trap::motor::DjiMotor::Config kPitchMotorConfig
    {
        .motorId        = tap::motor::MOTOR2,
        .canBus         = tap::can::CanBus::CAN_BUS1,
        .name           = "pitchMotor",
        .inverted       =  true,
        .currentControl = true 
    };

    static const motor::DualCascadeGm6020::PidMotor::Config kPitchMotorPidConfig
    {

        .mainPidConfig = kPitchPositionPid,
        .intermediatePidConfig = kPitchVelocityPid,
        .mainPidInitialValue = 0.0_rad,
        .intermediatePidInitialValue = 0.0_rpm,
    };

   

    static const trap::motor::DjiSpeedPid::Config kYawPositionPid
    {
        .kp                 = 80.0,
        .ki                 = 0.0,
        .kd                 = 0.0,
        .maxICumulative     = 0.0,
        .maxOutput          = trap::motor::DjiGM6020::kMaxOutput,
        .tQDerivativeKalman = 1.0, //Cause value to be more "sluggish to reduce oscillation"
        .tRDerivativeKalman = 0.0,
        .tQProportionalKalman = 1,
        .tRProportionalKalman = 100.0,
    };

    static const trap::motor::DjiSpeedPid::Config kYawVelocityPid
    {
        .kp                 = 475,
        .ki                 = 0,
        .kd                 = 0.0,
        .maxICumulative     = 0,
        .maxOutput          = trap::motor::DjiGM6020::kMaxOutput,
        .tQDerivativeKalman = 1.0, //Cause value to be more "sluggish to reduce oscillation"
        .tRDerivativeKalman = 0.0,
        .tQProportionalKalman = 1.0,
        .tRProportionalKalman = 200.0,
        .errorDerivativeFloor = 0 //rpm
    };

    static const turret::PierceFieldGimbal::YawSystem::Gm6020CounterChassisFieldYaw::ModdedCascadeMotor::Config kYawMotorPidConfig
    {
        .mainPidConfig = kYawPositionPid,
        .intermediatePidConfig = kYawVelocityPid
    };

    static const trap::motor::DjiGM6020::Config kYawMotorConfig 
    {
        .motorId        = tap::motor::MOTOR1,
        .canBus         = tap::can::CanBus::CAN_BUS1,
        .name           = "yawMotor",
        .inverted       = false,
        .currentControl = true 
    };

    static const motor::DualCascadeGm6020::Config kDualCascadePitchMotorConfig
    {
        .motorConfig = kPitchMotorConfig,
        .pidMotorConfig = kPitchMotorPidConfig 
    };

    static const turret::BasicFieldPitchSystem::Config kBasicFieldPitchConfig
    {
        .pitchError = 0_deg,
        .pitchRange = {
            .min = -20_deg,
            .max = 15_deg
        }
    };

    static const turret::PierceFieldGimbal::PitchSystem::Config kPitchSystemConfig
    {
        .motorConfig = kDualCascadePitchMotorConfig,
        .pitchSystemConfig = kBasicFieldPitchConfig
    };

    static const turret::PierceFieldGimbal::YawSystem::Config kYawSystemConfig 
    {
        .motorConfig = kYawMotorConfig,
        .fieldYawConfig = 
        {
            .chassisFieldYawConfig = {.yawError = -37_deg},
            .counterYawConfig = {.correctionScale = 1.0},
            .moddedCascadeConfig = kYawMotorPidConfig
        }
    };

    static const turret::PierceFieldGimbal::Config kGimbalSubsystemConfig
    {
        .pitchSystemConfig = kPitchSystemConfig,
        .yawSystemConfig = kYawSystemConfig
    };
    return kGimbalSubsystemConfig;
}
}