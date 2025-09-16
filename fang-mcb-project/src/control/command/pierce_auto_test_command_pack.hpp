#pragma once

#include "command_pack.hpp"

// Input
#include "control/turret/proxy_turret_input.hpp"
#include "control/turret/turret_input_handler.hpp"
#include "control/chassis/chassis_input_handler.hpp"

// Chassis Commands
#include "control/chassis/drive/holonomic/command/counter_strike_command.hpp"
#include "control/chassis/drive/holonomic/command/shuriken_command.hpp"
#include "control/chassis/drive/holonomic/command/tardis_command.hpp"

// Turret Commands
#include "control/turret/gimbal/command/positional_aim_command.hpp"
#include "control/turret/ammo_booster/command/activate_booster_command.hpp"
#include "control/turret/feeder/command/simple_autofire_command.hpp"
#include "control/turret/feeder/command/simple_unjam_command.hpp"

// Mapping Types
#include "tap/control/press_command_mapping.hpp"
#include "tap/control/hold_command_mapping.hpp"

#include "tap/control/remote_map_state.hpp"

namespace fang::command
{
    class PierceAutoTestCommandPack : public CommandPack
    {
    public:
        struct InputConfig
        {
            chassis::ChassisInputHandler::Config chassisInputConfig;
            turret::TurretInputHandler::Config turretInputConfig;
        };

        struct CommandConfig
        {
            turret::PositionalAimCommand::Config aimConfig;
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
            InputConfig inputConfig;
            MappingConfig mappingConfig;
            CommandConfig commandConfig;
        };

        PierceAutoTestCommandPack
        (
            Drivers& drivers, 
            turret::SimpleAmmoBoosterSubsystem& booster,
            turret::SimpleFeederSubsystem& feeder,
            turret::FieldGimbalSubsystem& gimbal,
            chassis::HolonomicSubsystem& chassis,
            const Config& config
        );

        virtual void initialize() override;
    private:
        void registerIoMappings();
        void setDefaultCommands();

        turret::SimpleAmmoBoosterSubsystem& booster_;
        turret::SimpleFeederSubsystem& feeder_;
        turret::FieldGimbalSubsystem& gimbal_;
        chassis::HolonomicSubsystem& chassis_;

        Drivers& drivers_;
        //Used only for initialization DO NOT ACCESS AFTERWARDS
        const CommandConfig& kCommandConfig_;
        const RemoteMapping& kRemoteMapping_;
        const ComputerMapping& kComputerMapping_;

        chassis::ChassisInputHandler chassisInput_;
        turret::ProxyTurretInput turretInput_{{1.0,1.0}};

        turret::PositionalAimCommand aim_{gimbal_, turretInput_, kCommandConfig_.aimConfig};
        turret::ActivateBoosterCommand activateBooster_{booster_};
        fang::turret::AutofireCommand autofire_{feeder_};
        fang::turret::UnjamCommand unjam_{feeder_};

        tap::control::HoldCommandMapping activateBoosterRemote_{&drivers_, {&activateBooster_}, kRemoteMapping_.activateBooster};
        tap::control::HoldCommandMapping activateAutofireRemote_{&drivers_, {&autofire_}, kRemoteMapping_.fire};

        tap::control::HoldCommandMapping activateAutofireMouseMap_{&drivers_, {&autofire_}, kComputerMapping_.mouseFire};
        tap::control::HoldCommandMapping unjamMouse_{&drivers_, {&unjam_}, kComputerMapping_.mouseUnjam};
        tap::control::HoldCommandMapping unjamRemote_{&drivers_, {&unjam_}, kRemoteMapping_.unjam};

        chassis::CounterStrikeCommand counterStrike_{chassis_, gimbal_, chassisInput_, kCommandConfig_.counterStrikeConfig};
        chassis::ShurikenCommand shuriken_{chassis_, gimbal_, chassisInput_, kCommandConfig_.shurikenConfig};
        chassis::TardisCommand tardis_{chassis_, gimbal_, chassisInput_, kCommandConfig_.tardisConfig};

        tap::control::HoldCommandMapping counterStrikeRemote_{&drivers_, {&counterStrike_}, kRemoteMapping_.counterStrike};
        tap::control::PressCommandMapping shurikenRemote_{&drivers_, {&shuriken_}, kRemoteMapping_.shuriken};
        tap::control::PressCommandMapping tardisRemote_{&drivers_, {&tardis_}, kRemoteMapping_.tardis};

        tap::control::PressCommandMapping counterStrikeKeyboard_{&drivers_, {&counterStrike_}, kComputerMapping_.counterStrike};
        tap::control::PressCommandMapping shruikenKeyboard_{&drivers_, {&shuriken_}, kComputerMapping_.shuriken};
        tap::control::PressCommandMapping tardisKeyboard_{&drivers_, {&tardis_}, kComputerMapping_.tardis};
    };
}