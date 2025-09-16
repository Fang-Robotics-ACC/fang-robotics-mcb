#include "pierce_auto_test_config.hpp"
#include "pierce_auto_test.hpp"

//Subsystem configs
#include "config/subsystem/chassis_config.hpp"
#include "config/subsystem/turret_gimbal_config.hpp"
#include "config/subsystem/feeder_config.hpp"
#include "config/subsystem/ammo_booster_config.hpp"

//Input configs 
#include "config/input/turret_input_config.hpp"
#include "config/input/chassis_input_config.hpp"

//Command configs
#include "config/command/turret_auto_aim_config.hpp"
#include "config/command/field_mecanum_config.hpp"
#include "config/command/shuriken_config.hpp"
#include "config/command/tardis_config.hpp"

//Mapping configs
#include "config/mapping/chassis_command_map.hpp"
#include "config/mapping/turret_command_map.hpp"

namespace fang::robot
{
    const PierceAutoTest::SubsystemConfig kPierceSubsystemConfig 
    {
        .chassisConfig  = kChassisConfig,
        .gimbalConfig   = kGimbalSubsystemConfig,
        .feederConfig   = kFeederMakerConfig,
        .boosterConfig  = kAmmoBoosterConfig
    };

    const command::PierceAutoTestCommandPack::InputConfig kPierceInputConfig 
    {
        .chassisInputConfig = kChassisInputConfig,
        .turretInputConfig  = kTurretInputConfig
    };

    const command::PierceAutoTestCommandPack::CommandConfig k_pierceCommandConfig
    {
        .aimConfig           = kTurretAimConfig,
        .counterStrikeConfig = kFieldMecanumConfig,
        .shurikenConfig      = kShurikenConfig,
        .tardisConfig        = k_tardisConfig
    };

    const command::PierceAutoTestCommandPack::ComputerMapping kPierceComputerMappingCOnfig 
    {
        .mouseFire     = kAutofireMouseState,
        .mouseUnjam    = kUnjamMouseState,
        .counterStrike = kFieldMecanumKeyboardState,
        .shuriken      = kShurikenModeKeyboardState,
        .tardis        = kTardisModeKeyboardState
    };

    const command::PierceAutoTestCommandPack::RemoteMapping kPierceRemoteMappingConfig 
    {
        .activateBooster = kActivateBoosterRemoteState,
        .fire            = kAutofireRemoteState,
        .unjam           = kUnjamRemoteState,
        .counterStrike   = kFieldMecanumRemoteState,
        .shuriken        = kShurikenModeRemoteState,
        .tardis          = kTardisModeRemoteState
    };

    const command::PierceAutoTestCommandPack::MappingConfig kPierceMappingConfig 
    {
        .remote     = kPierceRemoteMappingConfig,
        .computer   = kPierceComputerMappingCOnfig
    };

    const command::PierceAutoTestCommandPack::Config kPierceAutoTestCommandPackConfig
    {
        .inputConfig   = kPierceInputConfig,
        .mappingConfig = kPierceMappingConfig,
        .commandConfig = k_pierceCommandConfig
    };

    const PierceAutoTest::Config k_pierceAutoTestConfig
    {
        .subsystemConfig   = kPierceSubsystemConfig,
        .commandPackConfig = kPierceAutoTestCommandPackConfig
    };
}