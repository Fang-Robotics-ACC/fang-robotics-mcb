#ifndef FANG_ROBOTICS_MCB_AMMO_BOOSTER_CONFIG_HPP
#define FANG_ROBOTICS_MCB_AMMO_BOOSTER_CONFIG_HPP
#include "control/turret/flywheel_system.hpp"
#include "control/turret/ammo_booster_system.hpp"

#include "units.h"

namespace control
{
    using AmmoBooster = control::turret::AmmoBoosterSystem;
    using Flywheel = control::turret::FlywheelSystem;

    using namespace units::literals;


    static const trap::motor::DjiSpeedPid::Config k_flywheelMotorPidConfig 
    {
        10,
        10,
        0,
        100,
        trap::motor::DjiM3508::k_maxOutput
    };

    static const trap::motor::DjiSpeedPid::Config k_flywheelMotorPidConfigRight
    {
        10,
        10,
        0,
        100,
        trap::motor::DjiM3508::k_maxOutput
    };

    static const Flywheel::DriveMotor::Config k_leftFlywheelMotorConfig
    { 
        static_cast<tap::motor::MotorId>(tap::motor::MOTOR8),
        tap::can::CanBus::CAN_BUS1,
        "leftFlywheel",
        false,
        1.0,
        k_flywheelMotorPidConfig 
    };
    static const Flywheel::Config k_leftFlywheelConfig 
    {
        150_mm,
        k_leftFlywheelMotorConfig
    };

    static const Flywheel::DriveMotor::Config k_rightFlywheeMotorConfig 
    { 
        static_cast<tap::motor::MotorId>(tap::motor::MOTOR7),
        tap::can::CanBus::CAN_BUS1,
        "rightFlywheel",
        true,
        1.0,
        k_flywheelMotorPidConfigRight
    };

    static const Flywheel::Config k_rightFlywheelConfig
    {
        150_mm,
        k_rightFlywheeMotorConfig
    };

    static const AmmoBooster::Config k_ammoBoosterConfig
    {
        50_fps,
        k_leftFlywheelConfig,
        k_rightFlywheelConfig
    };

}
#endif