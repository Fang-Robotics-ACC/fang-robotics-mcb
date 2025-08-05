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

namespace fang::robot
{
    const Pierce::SubsystemConfig k_pierceSubsytemConfig 
    {
        .chassisConfig  = kChassisConfig,
        .gimbalConfig   = kGimbalSubsystemConfig,
        .feederConfig   = kFeederMakerConfig,
        .boosterConfig  = kAmmoBoosterConfig
    };

    const Pierce::InputConfig k_pierceInputConfig
    {
        .chassisInputConfig = k_chassisInputConfig,
        .turretInputConfig  = k_turretInputConfig
    };

    const Pierce::CommandConfig k_pierceCommandConfig
    {
        .aimCommandConfig   = k_turretAimConfig,
        .fieldMecanumConfig = k_fieldMecanumConfig,
        .shurikenConfig     = k_shurikenConfig,
        .tardisConfig       = k_tardisConfig
    };

    const Pierce::MappingConfig k_pierceMappingConfig
    {
        .remoteActivateBooster      = k_activateBoosterRemoteState,
        .remoteFire                 = k_autofireRemoteState,
        .remoteUnjam                = k_unjamRemoteState,
        .remoteFieldMecanumMode     = k_fieldMecanumRemoteState,
        .remoteShurikenMode         = k_shurikenModeRemoteState,
        .remoteTardisMode           = k_tardisModeRemoteState,
        .mouseFire                  = k_autofireMouseState,
        .mouseUnjam                 = k_unjamMouseState,
        .keyboardFieldMecanumMode   = k_fieldMecanumKeyboardState,
        .keyboardShurikenMode       = k_shurikenModeKeyboardState,
        .keyboardTardisMode         = k_tardisModeKeyboardState
    };

    const Pierce::Config k_pierceConfig
    {
        .subsystemConfig    = k_pierceSubsytemConfig,
        .inputConfig        = k_pierceInputConfig,
        .mappingConfig      = k_pierceMappingConfig,
        .commandConfig      = k_pierceCommandConfig
    };
}