#ifndef FANG_ROBOTICS_MCB_CHASSIS_CONFIG_PIERCE_HPP
#define FANG_ROBOTICS_MCB_CHASSIS_CONFIG_PIERCE_HPP

#include "robot/variant/pierce/custom_variant/subsystem/pierce_mecanum_drive.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::robot 
{
    using namespace units::literals;

    //pwm initialization
    static const auto kPwmTimer{tap::gpio::Pwm::TIMER1};
    static const Hertz kPwmFrequency{400};
    static const Volts kControllerInputVoltage{24};

    //All motors are assume to move counterclockwise when given a positive signal
    static bool kLeftMotorInversion{false};
    static bool kRightMotorInversion{true};

    static double kUltraMk2GearRatio{14.0};

    static double kMotorRampSpeed{750}; //RepeatUltraMk2 RPM per Second


    static const chassis::PierceMecanumDrive::Motor::Config kFrontLeftMotorConfig
    {
        .controllerInputVoltage = kControllerInputVoltage,
        .pwmData = {tap::gpio::Pwm::C1, kPwmFrequency},
        .inverted = kLeftMotorInversion,
        .gearRatio = kUltraMk2GearRatio,
        .rampSpeed = kMotorRampSpeed
    };

    static const chassis::PierceMecanumDrive::Motor::Config kFrontRightMotorConfig
    {
        .controllerInputVoltage = kControllerInputVoltage,
        .pwmData = {tap::gpio::Pwm::C2, kPwmFrequency},
        .inverted = kRightMotorInversion,
        .gearRatio = kUltraMk2GearRatio,
        .rampSpeed = kMotorRampSpeed
    };

    static const chassis::PierceMecanumDrive::Motor::Config kRearLeftMotorConfig
    {
        .controllerInputVoltage = kControllerInputVoltage,
        .pwmData = {tap::gpio::Pwm::C3, kPwmFrequency},
        .inverted = kLeftMotorInversion,
        .gearRatio = kUltraMk2GearRatio,
        .rampSpeed = kMotorRampSpeed
    };

    static const chassis::PierceMecanumDrive::Motor::Config kRearRightMotorConfig
    {
        .controllerInputVoltage = kControllerInputVoltage,
        .pwmData = {tap::gpio::Pwm::C4, kPwmFrequency},
        .inverted = kRightMotorInversion,
        .gearRatio = kUltraMk2GearRatio,
        .rampSpeed = kMotorRampSpeed
    };

    static const chassis::PierceMecanumDrive::MotorConfigs kMotorConfigs
    {
        .frontLeft = kFrontLeftMotorConfig,
        .frontRight = kFrontRightMotorConfig,
        .rearLeft = kRearLeftMotorConfig,
        .rearRight = kRearRightMotorConfig,
    };

    static const chassis::PierceMecanumDrive::PowerLimiter::Config kChassisPowerLimiterConfig
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

    static const chassis::PierceMecanumDrive::Config kChassisConfig 
    {
        .motorConfigs        = kMotorConfigs,
        .powerLimiterConfig  = kChassisPowerLimiterConfig,
        .fieldMecanumConfig  = kFieldMecanumLogicConfig,
        .chassisPwmFrequency = kPwmFrequency,
        .pwmTimer            = kPwmTimer,
    };

}
#endif