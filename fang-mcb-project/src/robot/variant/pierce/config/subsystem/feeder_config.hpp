#ifndef FANG_ROBOTICS_MCB_FEEDER_CONFIG_HPP
#define FANG_ROBOTICS_MCB_FEEDER_CONFIG_HPP
#include "control/turret/feeder/simple_feeder_subsystem/simple_feeder_subsystem.hpp"
#include "control/turret/feeder/simple_feeder_subsystem/m2006_simple_feeder_subsystem.hpp"
#include "wrap/trap/motor/dji_m2006.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::robot 
{

    using namespace units::literals;
    static const trap::motor::DjiSpeedPid::Config kFeederMotorPidConfig
    {
        20,
        0,
        0,
        100,
        trap::motor::DjiM2006::k_maxOutput
    };

    static const trap::motor::DjiM2006::Config kFeederMotorConfig
    { 
        tap::motor::MOTOR3,
        tap::can::CanBus::CAN_BUS1,
        "Feeder Motor",
        false,
        10,
        kFeederMotorPidConfig
    };


    static const fang::turret::SimpleFeederSystem::Config kFeederSystemConfig
    {
        .roundsPerRevolution    = 7,
        .feedRate               = 5_Hz,
        .unjamSpeed             = 30_rpm,
    };

    static const fang::turret::SimpleFeederSystem::Config kSimpleFeederSystemConfig
    {
        .roundsPerRevolution    = 7,
        .feedRate               = 5_Hz,
        .unjamSpeed             = 30_rpm,
    };

    static const fang::turret::SimpleFeederSubsystem::HeatLimiter::Config kFeederHeatLimiterConfig
    {
        .criticalHeatLimit  = 220,
        .turretId           = turret::TurretId::TURRET_17MM_1

    };

    static const fang::turret::M2006SimpleFeederSubsystem::Config kFeederMakerConfig
    {
        .feedMotorConfig = kFeederMotorConfig,
        .feederSubsystemConfig = {kFeederHeatLimiterConfig},
        .feederSystemConfig =  kSimpleFeederSystemConfig
    };
}
#endif