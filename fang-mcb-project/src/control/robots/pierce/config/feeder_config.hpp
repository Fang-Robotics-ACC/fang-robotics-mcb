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
        1.0,
        k_feederMotorPidConfig
    };

    static const turret::FeederSystem::Config k_feederConfig
    {
        7,
        25_Hz,
        k_feederMotorConfig
    };
}
#endif