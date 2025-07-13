#include "pierce_config.hpp"
#include "pierce.hpp"

//Subsystem configs
#include "config/subsystem/chassis_config.hpp"
#include "config/subsystem/turret_gimbal_config.hpp"
#include "config/subsystem/feeder_config.hpp"
#include "config/subsystem/ammo_booster_config.hpp"

//Input configs 
#include "config/input/turret_input_config.hpp"
#include "config/input/chassis_input_config.hpp"

//Command configs
#include "config/command/turret_aim_config.hpp"
#include "config/command/field_mecanum_config.hpp"
#include "config/command/shuriken_config.hpp"
#include "config/command/tardis_config.hpp"

//Mapping configs
#include "config/mapping/chassis_command_map.hpp"
#include "config/mapping/turret_command_map.hpp"

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
        k_turretInputConfig,
    };

    const Pierce::CommandConfig k_pierceCommandConfig
    {
        k_turretAimConfig,
        k_fieldMecanumConfig,
        k_shurikenConfig,
        k_tardisConfig,
    };

    const Pierce::MappingConfig k_pierceMappingConfig
    {
        k_activateBoosterRemoteState,
        k_autofireRemoteState,
        k_unjamRemoteState,
        k_fieldMecanumRemoteState,
        k_shurikenModeRemoteState,
        k_tardisModeRemoteState,
        k_autofireMouseState,
        k_unjamMouseState,
        k_fieldMecanumKeyboardState,
        k_shurikenModeKeyboardState,
        k_tardisModeKeyboardState
    };

    const Pierce::Config k_pierceConfig
    {
        k_pierceSubsytemConfig,
        k_pierceInputConfig,
        k_pierceCommandConfig,
        k_pierceMappingConfig
    };
}