#ifndef FANG_ROBOTICS_MCB_CHASSIS_CONFIG_HPP
#define FANG_ROBOTICS_MCB_CHASSIS_CONFIG_HPP
#include "control/chassis/chassis_subsystem.hpp"
#include "unitaliases.hpp"
namespace config 
{
    namespace chassis
    {
        using ChassisSubsystem = control::chassis::ChassisSubsystem;
        using namespace units::literals;
        static const Hertz k_chassisPwmFreq{500};
        
        static const ChassisSubsystem::ChassisDimensionConfig k_defaultDimensionConfig
        {
            150_mm, //Wheel Radius
            15_in,  //Vertical Wheel Distance
            13.5_in   //Horizontal Wheel Distance
        };

        static const ChassisSubsystem::DriveMotor::UnifiedProperties k_unifiedMotorProperties
        {
            24.0_V,                                      //Controller Input Voltage
            data::motors::Directionality::BIDIRECTIONAL, //Directionality
            14.0                                         //GearRatio
        };
        static const ChassisSubsystem::ChassisMotorConfig k_defaultMotorConfig
        {
            k_unifiedMotorProperties,                   //Unified motor properties
            trap::gpio::PwmData{tap::gpio::Pwm::C1, k_chassisPwmFreq},    //Front Left PwmData
            trap::gpio::PwmData{tap::gpio::Pwm::C2, k_chassisPwmFreq},    //Front Right PwmData
            trap::gpio::PwmData{tap::gpio::Pwm::C3, k_chassisPwmFreq},    //Rear Left PwmData
            trap::gpio::PwmData{tap::gpio::Pwm::C4, k_chassisPwmFreq}     //Rear Right PwmData
        };

        static const ChassisSubsystem::ChassisConfig k_defaultConfig
        {
            k_defaultDimensionConfig,
            k_defaultMotorConfig
        };
    }//namespace chassis
}//namespace control
#endif