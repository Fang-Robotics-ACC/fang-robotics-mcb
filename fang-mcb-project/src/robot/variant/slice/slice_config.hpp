#pragma once
#include "slice.hpp"
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
static const Slice::SubsystemConfig kSliceceSubsystemConfig 
{
    .chassisConfig  = kChassisConfig,
    .gimbalConfig   = kGimbalSubsystemConfig,
    .feederConfig   = kFeederMakerConfig,
    .boosterConfig  = kAmmoBoosterConfig
};

static const Slice::InputConfig kSliceInputConfig 
{
    .holonomic = kChassisInputConfig,
    .gimbal = kTurretInputConfig
};

static const command::PierceCommandPack::CommandConfig kSliceCommandConfig
{
    .aimConfig           = kTurretAimConfig,
    .counterStrikeConfig = kFieldMecanumConfig,
    .shurikenConfig      = kShurikenConfig,
    .tardisConfig        = k_tardisConfig
};

static const command::PierceCommandPack::ComputerMapping kSliceComputerMappingCOnfig 
{
    .mouseFire     = kAutofireMouseState,
    .mouseUnjam    = kUnjamMouseState,
    .counterStrike = kFieldMecanumKeyboardState,
    .shuriken      = kShurikenModeKeyboardState,
    .tardis        = kTardisModeKeyboardState
};

static const command::PierceCommandPack::RemoteMapping kSliceRemoteMappingConfig 
{
    .activateBooster = kActivateBoosterRemoteState,
    .fire            = kAutofireRemoteState,
    .unjam           = kUnjamRemoteState,
    .counterStrike   = kFieldMecanumRemoteState,
    .shuriken        = kShurikenModeRemoteState,
    .tardis          = kTardisModeRemoteState
};

static const command::PierceCommandPack::MappingConfig kSliceMappingConfig 
{
    .remote     = kSliceRemoteMappingConfig,
    .computer   = kSliceComputerMappingCOnfig
};

static const command::PierceCommandPack::Config kSliceCommandPackConfig
{
    .mappingConfig = kSliceMappingConfig,
    .commandConfig = kSliceCommandConfig
};

static const Slice::Config kSliceConfig
{
    .subsystemConfig   = kSliceceSubsystemConfig,
    .input = kSliceInputConfig,
    .commandPackConfig = kSliceCommandPackConfig
};
}