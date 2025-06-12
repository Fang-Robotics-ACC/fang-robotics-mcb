#ifndef FANG_ROBOTICS_MCB_PIERCE_TURRET_CONFIG_HPP
#define FANG_ROBOTICS_MCB_PIERCE_TURRET_CONFIG_HPP
#include "control/turret/gimbal_system.hpp"
#include "control/turret/turret_subsystem.hpp"
#include "control/robots/pierce/config/ammo_booster_config.hpp"
#include "control/robots/pierce/config/turret_gimbal_config.hpp"
#include "control/robots/pierce/config/feeder_config.hpp"
#include "unitaliases.hpp"
namespace control
{


    static const control::turret::TurretSubsystem::Config k_turretConfig
    {
        k_gimbalConfig,
        k_ammoBoosterConfig,
        k_feederConfig
    };

};
#endif