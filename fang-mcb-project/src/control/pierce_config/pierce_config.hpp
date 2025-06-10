#ifndef FANG_ROBOTICS_MCB_PIERCE_CONFIG_HPP
#define FANG_ROBOTICS_MCB_PIERCE_CONFIG_HPP
#include "control/pierce.hpp"
#include "control/pierce_config/pierce_chassis_config.hpp"
#include "control/pierce_config/pierce_turret_config.hpp"

#include "configuration/chassis_config.hpp"
namespace control 
{
    Pierce::Config k_defaultPierceConfig 
    {
        k_pierceChassisConfig,
        pierceConfig::k_turretConfig 
    };
}
#endif