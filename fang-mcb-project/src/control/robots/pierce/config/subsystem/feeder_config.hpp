#ifndef FANG_ROBOTICS_MCB_FEEDER_CONFIG_HPP
#define FANG_ROBOTICS_MCB_FEEDER_CONFIG_HPP
#include "control/turret/feeder_system.hpp"
#include "wrap/trap/motor/dji_m2006.hpp"

#include "unitaliases.hpp"
namespace control
{
    using namespace units::literals;
    static const trap::motor::DjiSpeedPid::Config k_feederMotorPidConfig 
    {
        5,
        100,
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
        trap::motor::DjiM2006::k_factoryGearboxRatio,
        k_feederMotorPidConfig
    };

    static const turret::FeederSystem::Config k_feederSystemConfig
    {
        7,
        10_Hz,
        k_feederMotorConfig
    };

    static const turret::FeederSubsystem::HeatLimiter::Config k_feederHeatLimiterConfig
    {
        .criticalHeatLimit  = 250,
        .turretId           = turret::TurretId::TURRET_17MM_1

    };

    static const turret::FeederSubsystem::Config k_feederConfig
    {
        k_feederHeatLimiterConfig,
        k_feederSystemConfig
    };
}
#endif