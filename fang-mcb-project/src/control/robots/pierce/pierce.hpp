#ifndef FANG_ROBOTICS_MCB_INFANTRY_HPP
#define FANG_ROBOTICS_MCB_INFANTRY_HPP
#include "drivers.hpp"
//Subsystems
#include "control/turret/turret_subsystem.hpp"
#include "control/chassis/chassis_subsystem.hpp"

#include "control/turret/gimbal_subsystem.hpp"
#include "control/turret/feeder_subsystem.hpp"
#include "control/turret/ammo_booster_subsystem.hpp"

//Input handlers
#include "control/turret/turret_input_handler.hpp"

//Commands
#include "control/chassis/field_mecanum_command.hpp"
#include "control/chassis/shuriken_command.hpp"
#include "control/chassis/tardis_command.hpp"

#include "control/turret/command/aim_command.hpp"
#include "control/turret/command/activate_booster_command.hpp"
#include "control/turret/command/autofire_command.hpp"
#include "control/turret/command/unjam_command.hpp"

#include "trap/communication/sensors/imu.hpp"

#include "tap/control/press_command_mapping.hpp"
#include "tap/control/hold_command_mapping.hpp"

namespace control
{
    /**
     * First Fang: Pierce
     * The first robot in Fang Robotics est. 2025
     */
    class Pierce
    {
    public:
        using RemoteState = tap::control::RemoteMapState;
        struct SubsystemConfig
        {
            chassis::ChassisSubsystem::ChassisConfig chassisConfig;
            turret::GimbalSubsystem::Config gimbalConfig;
            turret::FeederSubsystem::Config feederConfig;
            turret::AmmoBoosterSubsystem::Config boosterConfig;
        };

        struct InputConfig
        {
            chassis::ChassisInputHandler::Config chassisInputConfig;
            turret::TurretInputHandler::Config turretInputConfig;
        };

        struct CommandConfig
        {
            turret::AimCommand::Config aimCommandConfig;
            chassis::FieldMecanumCommand::Config fieldMecanumConfig;
            chassis::ShurikenCommand::Config shurikenConfig;
            chassis::TardisCommand::Config tardisConfig;
        };

        struct MappingConfig
        {
            RemoteState remoteActivateBooster;
            RemoteState remoteFire;
            RemoteState remoteFieldMecanumMode;
            RemoteState remoteShurikenMode;
            RemoteState remoteTardisMode;
            RemoteState mouseFire;
            RemoteState mouseUnjam;
            RemoteState keyboardFieldMecanumMode;
            RemoteState keyboardShurikenMode;
            RemoteState keyboardTardisMode;
        };

        struct Config
        {
            SubsystemConfig subsystemConfig;
            InputConfig inputConfig;
            CommandConfig commandConfig;
            MappingConfig mappingConfig;
        };

        Pierce(Drivers& drivers, const Config& config);
        void initialize();
    private:
        static constexpr Milliseconds k_startupDelay{1500};

        void initializeSubsystems();
        void setDefaultCommands();
        void registerIoMappings();

        const SubsystemConfig mk_subsystemConfig;
        const InputConfig mk_inputConfig;
        const CommandConfig mk_commandConfig;
        const MappingConfig mk_mappingConfig;

        Drivers& m_drivers;

        trap::communication::sensors::Imu m_imu;

        turret::GimbalSubsystem m_gimbal;
        turret::FeederSubsystem m_feeder;
        turret::AmmoBoosterSubsystem m_booster;
        chassis::ChassisSubsystem m_chassis;

        chassis::ChassisInputHandler m_chassisInput;
        turret::TurretInputHandler m_turretInput;

        turret::AimCommand m_aimCommnd{m_gimbal, m_turretInput, mk_commandConfig.aimCommandConfig};
        turret::ActivateBoosterCommand m_activateBoosterCommand{m_booster};
        turret::AutofireCommand m_autofireCommand{m_feeder};
        turret::UnjamCommand m_unjamCommand{m_feeder};

        tap::control::HoldCommandMapping m_activateBoosterRemoteMap{&m_drivers, {&m_activateBoosterCommand}, mk_mappingConfig.remoteActivateBooster};
        tap::control::HoldCommandMapping m_activateAutofireRemoteMap{&m_drivers, {&m_autofireCommand}, mk_mappingConfig.remoteFire};

        tap::control::HoldCommandMapping m_activateAutofireMouseMap{&m_drivers, {&m_autofireCommand}, mk_mappingConfig.mouseFire};
        tap::control::HoldCommandMapping m_unjamCommandMap{&m_drivers, {&m_unjamCommand}, mk_mappingConfig.mouseUnjam};

        chassis::FieldMecanumCommand m_fieldMecanumCommand{m_chassis, m_gimbal, m_chassisInput, mk_commandConfig.fieldMecanumConfig};
        chassis::ShurikenCommand m_shurikenCommand{m_chassis, m_gimbal, m_chassisInput, mk_commandConfig.shurikenConfig};
        chassis::TardisCommand m_tardisCommand{m_chassis, m_gimbal, m_chassisInput, mk_commandConfig.tardisConfig};

        tap::control::PressCommandMapping m_fieldMecanumRemoteMap{&m_drivers, {&m_fieldMecanumCommand}, mk_mappingConfig.remoteFieldMecanumMode};
        tap::control::PressCommandMapping m_shurikenRemoteMap{&m_drivers, {&m_shurikenCommand}, mk_mappingConfig.remoteShurikenMode};
        tap::control::PressCommandMapping m_tardisRemoteMap{&m_drivers, {&m_tardisCommand}, mk_mappingConfig.remoteTardisMode};

        tap::control::PressCommandMapping m_fieldMecanumKeyboardMap{&m_drivers, {&m_fieldMecanumCommand}, mk_mappingConfig.keyboardFieldMecanumMode};
        tap::control::PressCommandMapping m_shurikenKeyboardMap{&m_drivers, {&m_shurikenCommand}, mk_mappingConfig.keyboardShurikenMode};
        tap::control::PressCommandMapping m_tardisKeyboardMap{&m_drivers, {&m_tardisCommand}, mk_mappingConfig.keyboardTardisMode};
    };//class Robot
}//namspace control
#endif
