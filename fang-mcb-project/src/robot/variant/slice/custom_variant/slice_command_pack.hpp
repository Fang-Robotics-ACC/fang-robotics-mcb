#pragma once

#include "control/command/command_pack.hpp"

// Input
#include "control/turret/input/dji_gimbal_input.hpp"
#include "control/chassis/input/dji_holonomic_input.hpp"

// Chassis Commands
#include "control/chassis/drive/holonomic/command/counter_strike_command.hpp"
#include "control/chassis/drive/holonomic/command/shuriken_command.hpp"
#include "control/chassis/drive/holonomic/command/tardis_command.hpp"

// Turret Commands
#include "control/turret/gimbal/command/aim_command.hpp"
#include "control/turret/ammo_booster/command/activate_booster_command.hpp"
#include "control/turret/feeder/command/simple_fire_command.hpp"
#include "control/turret/feeder/command/simple_unjam_command.hpp"
#include "control/turret/gimbal/command/ballistics_aim_command.hpp"

// Mapping Types
#include "tap/control/press_command_mapping.hpp"
#include "tap/control/hold_command_mapping.hpp"

#include "tap/control/remote_map_state.hpp"

#include "wrap/trap/communication/sensors/iimu.hpp"

namespace fang::command
{
    class SliceCommandPack : public CommandPack
    {
    public:
        struct CommandConfig
        {
            turret::AimCommand::Config aimConfig;
            turret::BallisticsAimCommand::Config autoAimConfig;
            chassis::CounterStrikeCommand::Config counterStrikeConfig;
            chassis::ShurikenCommand::Config shurikenConfig;
            chassis::TardisCommand::Config tardisConfig;
        };

        struct RemoteMapping
        {
            RemoteState activateBooster;
            RemoteState fire;
            RemoteState unjam;
            RemoteState counterStrike;
            RemoteState shuriken;
            RemoteState tardis;
        };

        struct ComputerMapping
        {
            RemoteState mouseFire;
            RemoteState mouseUnjam;
            RemoteState counterStrike;
            RemoteState shuriken;
            RemoteState tardis;
        };

        struct MappingConfig
        {
            RemoteMapping remote;
            ComputerMapping computer;
        };

        struct Config
        {
            MappingConfig mappingConfig;
            CommandConfig commandConfig;
        };

        SliceCommandPack
        (
            Drivers& drivers, 
            turret::SimpleAmmoBoosterSubsystem& booster,
            turret::SimpleFeederSubsystem& feeder,
            turret::FieldGimbalSubsystem& gimbal,
            chassis::HolonomicSubsystem& chassis,
            turret::IGimbalInput& gimbalInput,
            chassis::IHolonomicInput& holonomicInput,
            communication::ICoolSerialUart& coolSerialUart,
            trap::communication::sensors::IImu& cameraOrientationImu,
            const Config& config
        );

        virtual void initialize() override;
    private:
        static const int kBasicTargetCoolSerialId{254};

        void registerIoMappings();
        void setDefaultCommands();

        turret::SimpleAmmoBoosterSubsystem& booster_;
        turret::SimpleFeederSubsystem& feeder_;
        turret::FieldGimbalSubsystem& gimbal_;
        chassis::HolonomicSubsystem& chassis_;
        communication::ICoolSerialUart& coolSerialUart_;
        trap::communication::sensors::IImu& cameraOrientationImu_;

        Drivers& drivers_;
        //Used only for initialization DO NOT ACCESS AFTERWARDS
        const CommandConfig& kCommandConfig_;
        const RemoteMapping& kRemoteMapping_;
        const ComputerMapping& kComputerMapping_;

        chassis::IHolonomicInput& holonomicInput_;
        turret::IGimbalInput& gimbalInput_;

        //Turret Commands
        turret::AimCommand aim_{gimbal_, gimbalInput_, kCommandConfig_.aimConfig};
        turret::ActivateBoosterCommand activateBooster_{booster_};
        fang::turret::FireCommand autofire_{feeder_};
        fang::turret::UnjamCommand unjam_{feeder_};
        turret::BallisticsAimCommand autoAim_{gimbal_, cameraOrientationImu_, kCommandConfig_.autoAimConfig};

        //HACK: IMPORTANT: THE MAPPING BELOW IS HIJACKED FOR TESTING, INCORRECT NAME
        tap::control::HoldCommandMapping activateBoosterRemote_{&drivers_, {&autoAim_}, kRemoteMapping_.activateBooster};
        tap::control::HoldCommandMapping activateAutofireRemote_{&drivers_, {&autofire_}, kRemoteMapping_.fire};

        tap::control::HoldCommandMapping activateAutofireMouseMap_{&drivers_, {&autofire_}, kComputerMapping_.mouseFire};
        tap::control::HoldCommandMapping unjamMouse_{&drivers_, {&unjam_}, kComputerMapping_.mouseUnjam};
        tap::control::HoldCommandMapping unjamRemote_{&drivers_, {&unjam_}, kRemoteMapping_.unjam};

        chassis::CounterStrikeCommand counterStrike_{chassis_, gimbal_, holonomicInput_, kCommandConfig_.counterStrikeConfig};
        chassis::ShurikenCommand shuriken_{chassis_, gimbal_, holonomicInput_, kCommandConfig_.shurikenConfig};
        chassis::TardisCommand tardis_{chassis_, gimbal_, holonomicInput_, kCommandConfig_.tardisConfig};

        tap::control::PressCommandMapping counterStrikeRemote_{&drivers_, {&counterStrike_}, kRemoteMapping_.counterStrike};
        tap::control::PressCommandMapping shurikenRemote_{&drivers_, {&shuriken_}, kRemoteMapping_.shuriken};
        tap::control::PressCommandMapping tardisRemote_{&drivers_, {&tardis_}, kRemoteMapping_.tardis};

        tap::control::PressCommandMapping counterStrikeKeyboard_{&drivers_, {&counterStrike_}, kComputerMapping_.counterStrike};
        tap::control::PressCommandMapping shruikenKeyboard_{&drivers_, {&shuriken_}, kComputerMapping_.shuriken};
        tap::control::PressCommandMapping tardisKeyboard_{&drivers_, {&tardis_}, kComputerMapping_.tardis};
    };
}