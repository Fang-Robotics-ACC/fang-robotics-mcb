#include "slice_command_pack.hpp"

namespace fang::command
{
        SliceCommandPack::SliceCommandPack
        (
            Drivers& drivers, 
            turret::SimpleAmmoBoosterSubsystem& booster,
            turret::SimpleFeederSubsystem& feeder,
            turret::FieldGimbalSubsystem& gimbal,
            chassis::HolonomicSubsystem& chassis,
            turret::IGimbalInput& gimbalInput,
            chassis::IHolonomicInput& holonomicInput,
            communication::ICoolSerialUart& coolSerialUart,
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
            holonomicInput_{holonomicInput},
            coolSerialUart_{coolSerialUart},
            gimbalInput_{gimbalInput}
        {}

    void SliceCommandPack::initialize()
    {
        setDefaultCommands();
        registerIoMappings();
    }

    void SliceCommandPack::setDefaultCommands()
    {
        gimbal_.setDefaultCommand(&aim_);
    }

    void SliceCommandPack::registerIoMappings()
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