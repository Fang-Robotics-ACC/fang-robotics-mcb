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
const Pierce::Config& getPierceConfig()
{
    static const Pierce::SubsystemConfig kPierceSubsystemConfig 
    {
        .chassisConfig  = kChassisConfig,
        .gimbalConfig   = kGimbalSubsystemConfig,
        .feederConfig   = kFeederMakerConfig,
        .boosterConfig  = kAmmoBoosterConfig
    };

    static const command::PierceCommandPack::InputConfig kPierceInputConfig 
    {
        .chassisInputConfig = kChassisInputConfig,
        .turretInputConfig  = kTurretInputConfig
    };

    static const command::PierceCommandPack::CommandConfig kPierceCommandConfig
    {
        .aimConfig           = kTurretAimConfig,
        .counterStrikeConfig = kFieldMecanumConfig,
        .shurikenConfig      = kShurikenConfig,
        .tardisConfig        = k_tardisConfig
    };

    static const command::PierceCommandPack::ComputerMapping kPierceComputerMappingCOnfig 
    {
        .mouseFire     = kAutofireMouseState,
        .mouseUnjam    = kUnjamMouseState,
        .counterStrike = kFieldMecanumKeyboardState,
        .shuriken      = kShurikenModeKeyboardState,
        .tardis        = kTardisModeKeyboardState
    };

    static const command::PierceCommandPack::RemoteMapping kPierceRemoteMappingConfig 
    {
        .activateBooster = kActivateBoosterRemoteState,
        .fire            = kAutofireRemoteState,
        .unjam           = kUnjamRemoteState,
        .counterStrike   = kFieldMecanumRemoteState,
        .shuriken        = kShurikenModeRemoteState,
        .tardis          = kTardisModeRemoteState
    };

    static const command::PierceCommandPack::MappingConfig kPierceMappingConfig 
    {
        .remote     = kPierceRemoteMappingConfig,
        .computer   = kPierceComputerMappingCOnfig
    };

    static const command::PierceCommandPack::Config kPierceCommandPackConfig
    {
        .inputConfig   = kPierceInputConfig,
        .mappingConfig = kPierceMappingConfig,
        .commandConfig = kPierceCommandConfig
    };

    static const Pierce::Config kPierceConfig
    {
        .subsystemConfig   = kPierceSubsystemConfig,
        .commandPackConfig = kPierceCommandPackConfig
    };

    return kPierceConfig;
}
}