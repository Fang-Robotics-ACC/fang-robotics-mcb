#pragma once
#include "pierce.hpp"
namespace fang::robot 
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
}