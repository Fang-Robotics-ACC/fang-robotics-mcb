#ifndef FANG_ROBOTICS_MCB_CHASSIS_CONFIG_PIERCE_HPP
#define FANG_ROBOTICS_MCB_CHASSIS_CONFIG_PIERCE_HPP
#include "control/chassis/chassis_subsystem.hpp"
#include "unitaliases.hpp"

namespace control
{
    static const Hertz k_chassisPwmFreq{400};

    using namespace units::literals;
        
    static const chassis::ChassisSubsystem::ChassisDimensionConfig k_defaultDimensionConfig
    {
        150_mm, //Wheel Radius
        15_in,  //Vertical Wheel Distance
        13.5_in   //Horizontal Wheel Distance
    };

    static const chassis::ChassisSubsystem::DriveMotor::UnifiedProperties k_unifiedMotorProperties
    {
        24.0_V,                                      //Controller Input Voltage
        data::motors::Directionality::BIDIRECTIONAL, //Directionality
        14.0                                         //GearRatio
    };
    static const chassis::ChassisSubsystem::ChassisMotorConfig k_defaultMotorConfig
    {
        k_unifiedMotorProperties,                   //Unified motor properties
        trap::gpio::PwmData{tap::gpio::Pwm::C1, k_chassisPwmFreq},    //Front Left PwmData
        trap::gpio::PwmData{tap::gpio::Pwm::C2, k_chassisPwmFreq},    //Front Right PwmData
        trap::gpio::PwmData{tap::gpio::Pwm::C3, k_chassisPwmFreq},    //Rear Left PwmData
        trap::gpio::PwmData{tap::gpio::Pwm::C4, k_chassisPwmFreq}     //Rear Right PwmData
    };

    static const chassis::ChassisSubsystem::PowerLimiter::Config k_chassisPowerLimiterConfig
    {
        .startingEnergyBuffer       = 80_J,
        .energyBufferLimitThreshold = 20_J,
        .energyBufferCritThreshold  = 140_J
    };

    static const chassis::ChassisSubsystem::ChassisConfig k_chassisConfig 
    {
        .pwmFrequency           = k_chassisPwmFreq,
        .pwmTimer               = tap::gpio::Pwm::TIMER1,
        .translationRampSpeed   = 15,
        .rotationRampSpeed      = 30,
        .chassisDimensions      = k_defaultDimensionConfig,
        .chassisMotors          = k_defaultMotorConfig,
        .powerLimiterConfig     = k_chassisPowerLimiterConfig
    };
}
#endif