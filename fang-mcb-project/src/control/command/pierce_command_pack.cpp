#pragma once

#include "pierce_command_pack.hpp"

namespace fang::command
{
        PierceCommandPack::PierceCommandPack
        (
            Drivers& drivers, 
            turret::SimpleAmmoBoosterSubsystem& booster,
            turret::SimpleFeederSubsystem& feeder,
            turret::FieldGimbalSubsystem& gimbal,
            chassis::HolonomicSubsystem& chassis,
            const Config& config
        ):
            CommandPack{drivers.commandMapper},

            kCommandConfig_{config.commandConfig},
            kRemoteMapping_{config.mappingConfig.remote},
            kComputerMapping_{config.mappingConfig.computer},
            drivers_{drivers},
            booster_{booster},
            feeder_{feeder},
            gimbal_{gimbal},
            chassis_{chassis},
            chassisInput_{drivers.remote, config.inputConfig.chassisInputConfig},
            turretInput_{drivers.remote, config.inputConfig.turretInputConfig}
        {}

    void PierceCommandPack::setDefaultCommands()
    {
        gimbal_.setDefaultCommand(&aim_);
    }

    void PierceCommandPack::registerIoMappings()
    {
        drivers_.commandMapper.addMap(&activateBoosterRemote_);
        drivers_.commandMapper.addMap(&activateAutofireRemote_);
        drivers_.commandMapper.addMap(&activateAutofireMouseMap_);
        drivers_.commandMapper.addMap(&unjamMouse_);
        drivers_.commandMapper.addMap(&unjamRemote_);

        drivers_.commandMapper.addMap(&counterStrikeRemote_);
        drivers_.commandMapper.addMap(&shurikenRemote_);
        drivers_.commandMapper.addMap(&tardisRemote_);

        drivers_.commandMapper.addMap(&counterStrikeKeyboard_);
        drivers_.commandMapper.addMap(&shruikenKeyboard_);
        drivers_.commandMapper.addMap(&tardisRemote_);
    }
}