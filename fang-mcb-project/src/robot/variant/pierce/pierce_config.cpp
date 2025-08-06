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
    const Pierce::SubsystemConfig kPierceSubsystemConfig 
    {
        .chassisConfig  = kChassisConfig,
        .gimbalConfig   = kGimbalSubsystemConfig,
        .feederConfig   = kFeederMakerConfig,
        .boosterConfig  = kAmmoBoosterConfig
    };

    const command::PierceCommandPack::InputConfig kPierceInputConfig 
    {
        .chassisInputConfig = k_chassisInputConfig,
        .turretInputConfig  = k_turretInputConfig
    };

    const command::PierceCommandPack::CommandConfig k_pierceCommandConfig
    {
        .aimConfig           = k_turretAimConfig,
        .counterStrikeConfig = k_fieldMecanumConfig,
        .shurikenConfig      = k_shurikenConfig,
        .tardisConfig        = k_tardisConfig
    };

    const command::PierceCommandPack::ComputerMapping kPierceComputerMappingCOnfig 
    {
        .mouseFire     = k_autofireMouseState,
        .mouseUnjam    = k_unjamMouseState,
        .counterStrike = k_fieldMecanumKeyboardState,
        .shuriken      = k_shurikenModeKeyboardState,
        .tardis        = k_tardisModeKeyboardState
    };

    const command::PierceCommandPack::RemoteMapping kPierceRemoteMappingConfig 
    {
        .activateBooster = k_activateBoosterRemoteState,
        .fire            = k_autofireRemoteState,
        .unjam           = k_unjamRemoteState,
        .counterStrike   = k_fieldMecanumRemoteState,
        .shuriken        = k_shurikenModeRemoteState,
        .tardis          = k_tardisModeRemoteState
    };

    const command::PierceCommandPack::MappingConfig kPierceMappingConfig 
    {
        .remote     = kPierceRemoteMappingConfig,
        .computer   = kPierceComputerMappingCOnfig
    };

    const command::PierceCommandPack::Config kPierceCommandPackConfig
    {
        .inputConfig   = kPierceInputConfig,
        .mappingConfig = kPierceMappingConfig,
        .commandConfig = k_pierceCommandConfig
    };

    const Pierce::Config k_pierceConfig
    {
        .subsystemConfig   = kPierceSubsystemConfig,
        .commandPackConfig = kPierceCommandPackConfig
    };
}