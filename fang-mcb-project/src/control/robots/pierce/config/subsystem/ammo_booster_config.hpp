#ifndef FANG_ROBOTICS_MCB_AMMO_BOOSTER_CONFIG_HPP
#define FANG_ROBOTICS_MCB_AMMO_BOOSTER_CONFIG_HPP
#include "control/turret/systems/flywheel_system.hpp"
#include "control/turret/systems/ammo_booster_system.hpp"
#include "unitaliases.hpp"

#include "units.h"

namespace control
{
    using AmmoBooster = control::turret::AmmoBoosterSystem;
    using Flywheel = control::turret::FlywheelSystem;

    using namespace units::literals;

    static const Meters k_flywheelRadius{30_mm};

    static const trap::motor::DjiSpeedPid::Config k_flywheelMotorPidConfig 
    {
        .kp             = 30,
        .ki             = 0,
        .kd             = 4000,
        .maxICumulative = 0,
        .maxOutput      = trap::motor::DjiM3508::k_maxOutput
    };

    static const Flywheel::DriveMotor::Config k_leftFlywheelMotorConfig
    { 
        .motorId        = tap::motor::MOTOR8,
        .canBus         = tap::can::CanBus::CAN_BUS1,
        .name           = "leftFlywheel",
        .inverted       = false,
        .gearRatio      = 1.0, //No gearbox attached
        .speedPidConfig = k_flywheelMotorPidConfig
    };

    static const Flywheel::Config k_leftFlywheelConfig 
    {
        k_flywheelRadius,
        k_leftFlywheelMotorConfig
    };

    static const Flywheel::DriveMotor::Config k_rightFlywheeMotorConfig 
    { 
        .motorId        = tap::motor::MOTOR7,
        .canBus         = tap::can::CanBus::CAN_BUS1,
        .name           = "rightFlywheel",
        .inverted       = true,
        .gearRatio      = 1.0, //No gearbox attached
        .speedPidConfig = k_flywheelMotorPidConfig
    };

    static const Flywheel::Config k_rightFlywheelConfig
    {
        k_flywheelRadius,
        k_rightFlywheeMotorConfig
    };

    static const AmmoBooster::Config k_ammoBoosterConfig
    {
        .ammoVelocity           = 25_mps,
        .leftFlywheelConfig     = k_leftFlywheelConfig,
        .rightFlywheelConfig    = k_rightFlywheelConfig
    };
}
#endif