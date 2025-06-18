#include "pierce_config.hpp"
#include "control/robots/pierce/pierce.hpp"

//Subsystem configs
#include "config/subsystem/chassis_config.hpp"
#include "config/subsystem/turret_gimbal_config.hpp"
#include "config/subsystem/feeder_config.hpp"
#include "config/subsystem/ammo_booster_config.hpp"

//Input configs 
#include "config/turret_input_config.hpp"
#include "config/chassis_input_config.hpp"

//Command configs
#include "config/command/turret_aim_config.hpp"
#include "config/command/field_mecanum_config.hpp"
#include "config/command/shuriken_config.hpp"

namespace control
{
    const Pierce::SubsystemConfig k_pierceSubsytemConfig 
    {
        k_chassisConfig,
        k_gimbalSubsystemConfig,
        k_feederConfig,
        k_ammoBoosterConfig
    };

    const Pierce::InputConfig k_pierceInputConfig
    {
        k_chassisInputConfig,
        k_turretInputRemoteConfig,
    };

    const Pierce::CommandConfig k_pierceCommandConfig
    {
        k_turretAimConfig,
        k_fieldMecanumConfig,
        k_shurikenConfig
    };

    const Pierce::Config k_pierceConfig
    {
        k_pierceSubsytemConfig,
        k_pierceInputConfig,
        k_pierceCommandConfig
    };
}