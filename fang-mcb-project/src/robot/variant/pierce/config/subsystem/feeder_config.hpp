#ifndef FANG_ROBOTICS_MCB_FEEDER_CONFIG_HPP
#define FANG_ROBOTICS_MCB_FEEDER_CONFIG_HPP
#include "control/turret/system/feeder_system.hpp"
#include "control/turret/feeder_subsystem.hpp"
#include "control/turret/feeder/simple_feeder_subsystem/m2006_simple_feeder_subsystem_maker.hpp"
#include "wrap/trap/motor/dji_m2006.hpp"
#include "wrap/units/units_alias.hpp"

namespace control
{
    using namespace units::literals;
    static const trap::motor::DjiSpeedPid::Config k_feederMotorPidConfig 
    {
        20,
        0,
        0,
        100,
        trap::motor::DjiM2006::k_maxOutput
    };

    static const trap::motor::DjiM2006::Config k_feederMotorConfig
    { 
        tap::motor::MOTOR3,
        tap::can::CanBus::CAN_BUS1,
        "Feeder Motor",
        false,
        10,
        k_feederMotorPidConfig
    };


    static const turret::FeederSystem::Config k_feederSystemConfig
    {
        .roundsPerRevolution    = 7,
        .feedRate               = 5_Hz,
        .unjamSpeed             = 30_rpm,
        .motorConfig            = k_feederMotorConfig
    };

    static const turret::SimpleFeederSystem::Config kSimpleFeederSystemConfig
    {
        .roundsPerRevolution    = 7,
        .feedRate               = 5_Hz,
        .unjamSpeed             = 30_rpm,
    };

    static const turret::FeederSubsystem::HeatLimiter::Config k_feederHeatLimiterConfig
    {
        .criticalHeatLimit  = 220,
        .turretId           = turret::TurretId::TURRET_17MM_1

    };

    static const turret::FeederSubsystem::Config k_feederConfig
    {
        k_feederHeatLimiterConfig,
        k_feederSystemConfig
    };

    static const turret::M2006SimpleFeederSubsystemMaker::Config kFeederMakerConfig
    {
        .feedMotorConfig = k_feederMotorConfig,
        .feederSubsystemConfig = {k_feederHeatLimiterConfig},
        .feederSystemConfig =  kSimpleFeederSystemConfig
    };
}
#endif