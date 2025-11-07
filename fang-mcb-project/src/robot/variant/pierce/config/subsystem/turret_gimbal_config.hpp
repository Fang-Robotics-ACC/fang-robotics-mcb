#pragma once

#include "robot/variant/pierce/custom_variant/subsystem/pierce_field_gimbal.hpp"

namespace fang::robot 
{
    using namespace units::literals;
    
    static const trap::motor::DjiSpeedPid::Config kPitchPositionPid
    {
        .kp                 = 30.0,
        .ki                 = 0.0,
        .kd                 = 0.0,
        .maxICumulative     = 0.0,
        .maxOutput          = trap::motor::DjiGM6020::kMaxOutput,
        .tQDerivativeKalman = 1.0, //Cause value to be more "sluggish to reduce oscillation"
        .tRDerivativeKalman = 0.0,
        .tQProportionalKalman = 1.0,
        .tRProportionalKalman = 40'000.0,
    };

    static const trap::motor::DjiSpeedPid::Config kPitchVelocityPid
    {
        .kp                 = 3'000,
        .ki                 = 0,
        .kd                 = 0.0,
        .maxICumulative     = 0,
        .maxOutput          = trap::motor::DjiGM6020::kMaxOutput,
        .tQDerivativeKalman = 1.0, //Cause value to be more "sluggish to reduce oscillation"
        .tRDerivativeKalman = 0.0,
        .tQProportionalKalman = 1,
        .tRProportionalKalman = 50'000.0,
    };

    static const trap::motor::DjiMotor::Config kPitchMotorConfig
    {
        .motorId        = tap::motor::MOTOR2,
        .canBus         = tap::can::CanBus::CAN_BUS1,
        .name           = "pitchMotor",
        .inverted       =  false,
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
        .kp                 = 70.0,
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
        .kp                 = 600,
        .ki                 = 0,
        .kd                 = 0.0,
        .maxICumulative     = 0,
        .maxOutput          = trap::motor::DjiGM6020::kMaxOutput,
        .tQDerivativeKalman = 1.0, //Cause value to be more "sluggish to reduce oscillation"
        .tRDerivativeKalman = 0.0,
        .tQProportionalKalman = 1.0,
        .tRProportionalKalman = 250.0,
        .errorDerivativeFloor = 00 //rpm
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

     static const motor::DualCascadeGm6020::Config kDualCascadeYawMotorConfig
    {
        .motorConfig = kYawMotorConfig,
        .pidMotorConfig = kYawMotorPidConfig 
    };

    static const turret::BasicFieldPitchSystem::Config kBasicFieldPitchConfig
    {
        .pitchError = 0_deg,
        .pitchRange = 
            {
                .min = -20_deg,
                .max = 15_deg
            }
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
            .yawError = -37_deg
        }
    };

    static const turret::PierceFieldGimbal::Config kGimbalSubsystemConfig
    {
        .pitchSystemConfig = kPitchSystemConfig,
        .yawSystemConfig = kYawSystemConfig
    };
}