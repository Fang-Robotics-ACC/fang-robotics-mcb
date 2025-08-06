#ifndef FANG_ROBOTICS_MCB_AMMO_BOOSTER_CONFIG_HPP
#define FANG_ROBOTICS_MCB_AMMO_BOOSTER_CONFIG_HPP
#include "robot/variant/pierce/custom_variant/subsystem/pierce_ammo_booster.hpp"
#include "wrap/units/units_alias.hpp"

#include "units.h"

namespace fang::robot 
{
    using AmmoBooster = turret::PierceAmmoBooster;
    using Flywheel = AmmoBooster::Flywheel;

    using namespace units::literals;

    static const Meters kFlywheelRadius{30_mm};

    static const trap::motor::DjiSpeedPid::Config kFlywheelMotorPidConfig 
    {
        .kp             = 10,
        .ki             = 0,
        .kd             = 0,
        .maxICumulative = 0,
        .maxOutput      = trap::motor::DjiM3508::k_maxOutput
    };

    static const Flywheel::Motor::Config kLeftFlywheelMotorConfig
    { 
        .motorId        = tap::motor::MOTOR8,
        .canBus         = tap::can::CanBus::CAN_BUS1,
        .name           = "leftFlywheel",
        .inverted       = false,
        .gearRatio      = 1.0, //No gearbox attached
        .speedPidConfig = kFlywheelMotorPidConfig
    };

    static const Flywheel::Config kLeftFlywheelConfig 
    {
        .radius         = kFlywheelRadius,
        .motorConfig    = kLeftFlywheelMotorConfig
    };

    static const Flywheel::Motor::Config kRightFlywheeMotorConfig 
    { 
        .motorId        = tap::motor::MOTOR7,
        .canBus         = tap::can::CanBus::CAN_BUS1,
        .name           = "rightFlywheel",
        .inverted       = true,
        .gearRatio      = 1.0, //No gearbox attached
        .speedPidConfig = kFlywheelMotorPidConfig
    };

    static const Flywheel::Config kRightFlywheelConfig
    {
        .radius         = kFlywheelRadius,
        .motorConfig    = kRightFlywheeMotorConfig
    };

    static const AmmoBooster::Config kAmmoBoosterConfig
    {
        .ammoVelocity           = 18_mps,
        .leftFlywheelConfig     = kLeftFlywheelConfig,
        .rightFlywheelConfig    = kRightFlywheelConfig
    };
}
#endif