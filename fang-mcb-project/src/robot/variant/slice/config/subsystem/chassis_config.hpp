#pragma once

#include "robot/variant/slice/custom_variant/subsystem/slice_mecanum_drive.hpp"
#include "wrap/units/units_alias.hpp"
#include "wrap/trap/motor/dji_motor_aliases.hpp"

#include "tap/algorithms/smooth_pid.hpp"

namespace fang::robot 
{
// Construct on first use idiom ahhhh
using namespace units::literals;

//All motors are assume to move counterclockwise when given a positive signal
static bool kLeftMotorInversion{false};
static bool kRightMotorInversion{true};

// M3580 Pid Config
trap::motor::DjiMotorOutput M3508maxOutput{trap::motor::DjiM3508Old::k_maxOutput};
tap::algorithms::SmoothPidConfig M3508PidConfig{.kp = 100, .ki = 0.0f, .kd = 0.0f, .maxICumulative = 0.0f, .maxOutput = M3508maxOutput};

static const chassis::SliceMecanumDrive::Motor::Config kFrontLeftMotorConfig
{   
    .motorId = tap::motor::MotorId::MOTOR1,
    .canBus = tap::can::CanBus::CAN_BUS2,
    .name = "FL",
    .inverted = kLeftMotorInversion,
    .gearRatio = tap::motor::DjiMotorEncoder::GEAR_RATIO_M3508,
    .speedPidConfig = M3508PidConfig

};

static const chassis::SliceMecanumDrive::Motor::Config kFrontRightMotorConfig
{
    .motorId = tap::motor::MotorId::MOTOR2,
    .canBus = tap::can::CanBus::CAN_BUS2,
    .name = "FR",
    .inverted = kRightMotorInversion,
    .gearRatio = tap::motor::DjiMotorEncoder::GEAR_RATIO_M3508,
    .speedPidConfig = M3508PidConfig
};

static const chassis::SliceMecanumDrive::Motor::Config kRearLeftMotorConfig
{
    .motorId = tap::motor::MotorId::MOTOR3,
    .canBus = tap::can::CanBus::CAN_BUS2,
    .name = "RL",
    .inverted = kLeftMotorInversion,
    .gearRatio = tap::motor::DjiMotorEncoder::GEAR_RATIO_M3508,
    .speedPidConfig = M3508PidConfig
};

static const chassis::SliceMecanumDrive::Motor::Config kRearRightMotorConfig
{
    .motorId = tap::motor::MotorId::MOTOR4,
    .canBus = tap::can::CanBus::CAN_BUS2,
    .name = "RR",
    .inverted = kRightMotorInversion,
    .gearRatio = tap::motor::DjiMotorEncoder::GEAR_RATIO_M3508,
    .speedPidConfig = M3508PidConfig
};

static const chassis::SliceMecanumDrive::MotorConfigs kMotorConfigs
{
    .frontLeft = kFrontLeftMotorConfig,
    .frontRight = kFrontRightMotorConfig,
    .rearLeft = kRearLeftMotorConfig,
    .rearRight = kRearRightMotorConfig,
};

static const chassis::SliceMecanumDrive::PowerLimiter::Config kChassisPowerLimiterConfig
{
    .startingEnergyBuffer       = 80_J,
    .energyBufferLimitThreshold = 5_J,
    .energyBufferCritThreshold  = 30_J
};

static const chassis::FieldMecanumLogic::Config kFieldMecanumLogicConfig
{
    150_mm, //Wheel Radius
    15_in,  //Vertical Wheel Distance
    13.5_in   //Horizontal Wheel Distance
};

static const chassis::SliceMecanumDrive::Config kChassisConfig 
{
    .motorConfigs        = kMotorConfigs,
    .powerLimiterConfig  = kChassisPowerLimiterConfig,
    .fieldMecanumConfig  = kFieldMecanumLogicConfig
};
}
