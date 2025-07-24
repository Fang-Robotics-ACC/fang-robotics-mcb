#ifndef FANG_ROBOTICS_MCB_INFANTRY_HPP
#define FANG_ROBOTICS_MCB_INFANTRY_HPP
#include "driver/drivers.hpp"
//Subsystems
#include "control/chassis/chassis_subsystem.hpp"

#include "control/turret/gimbal_subsystem.hpp"
#include "control/turret/feeder/simple_feeder_subsystem/simple_feeder_subsystem.hpp"
#include "control/turret/feeder/simple_feeder_subsystem/m2006_simple_feeder_subsystem_factory.hpp"
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

using namespace fang;

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
            fang::turret::M2006SimpleFeederSubsystemFactory::Config feederConfig;
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
            RemoteState remoteUnjam;
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
            MappingConfig mappingConfig;
            CommandConfig commandConfig;
        };

        Pierce(Drivers& drivers, const Config& config);
        void initialize();
    private:
        static constexpr Milliseconds k_startupDelay{1500};

        void initializeSubsystems();
        void setDefaultCommands();
        void registerIoMappings();

        Drivers& m_drivers;

        const SubsystemConfig mk_subsystemConfig;
        const InputConfig mk_inputConfig;
        const MappingConfig kMappingConfig_;
        const CommandConfig mk_commandConfig;


        trap::communication::sensors::Imu m_imu;

        turret::GimbalSubsystem m_gimbal;
        std::unique_ptr<fang::turret::SimpleFeederSubsystem> feeder_;
        fang::turret::SimpleFeederSubsystem& m_feeder{*feeder_};
        turret::AmmoBoosterSubsystem m_booster;
        chassis::ChassisSubsystem m_chassis;

        chassis::ChassisInputHandler m_chassisInput;
        turret::TurretInputHandler m_turretInput;

        turret::AimCommand m_aimCommnd{m_gimbal, m_turretInput, mk_commandConfig.aimCommandConfig};
        turret::ActivateBoosterCommand m_activateBoosterCommand{m_booster};
        fang::turret::AutofireCommand m_autofireCommand{m_feeder};
        fang::turret::UnjamCommand m_unjamCommand{m_feeder};

        tap::control::HoldCommandMapping m_activateBoosterRemoteMap{&m_drivers, {&m_activateBoosterCommand}, kMappingConfig_.remoteActivateBooster};
        tap::control::HoldCommandMapping m_activateAutofireRemoteMap{&m_drivers, {&m_autofireCommand}, kMappingConfig_.remoteFire};

        tap::control::HoldCommandMapping m_activateAutofireMouseMap{&m_drivers, {&m_autofireCommand}, kMappingConfig_.mouseFire};
        tap::control::HoldCommandMapping m_unjamCommandMap{&m_drivers, {&m_unjamCommand}, kMappingConfig_.mouseUnjam};
        tap::control::HoldCommandMapping m_unjamCommandMapRemote{&m_drivers, {&m_unjamCommand}, kMappingConfig_.remoteUnjam};

        chassis::FieldMecanumCommand m_fieldMecanumCommand{m_chassis, m_gimbal, m_chassisInput, mk_commandConfig.fieldMecanumConfig};
        chassis::ShurikenCommand m_shurikenCommand{m_chassis, m_gimbal, m_chassisInput, mk_commandConfig.shurikenConfig};
        chassis::TardisCommand m_tardisCommand{m_chassis, m_gimbal, m_chassisInput, mk_commandConfig.tardisConfig};

        tap::control::HoldCommandMapping m_fieldMecanumRemoteMap{&m_drivers, {&m_fieldMecanumCommand}, kMappingConfig_.remoteFieldMecanumMode};
        tap::control::PressCommandMapping m_shurikenRemoteMap{&m_drivers, {&m_shurikenCommand}, kMappingConfig_.remoteShurikenMode};
        tap::control::PressCommandMapping m_tardisRemoteMap{&m_drivers, {&m_tardisCommand}, kMappingConfig_.remoteTardisMode};

        tap::control::PressCommandMapping m_fieldMecanumKeyboardMap{&m_drivers, {&m_fieldMecanumCommand}, kMappingConfig_.keyboardFieldMecanumMode};
        tap::control::PressCommandMapping m_shurikenKeyboardMap{&m_drivers, {&m_shurikenCommand}, kMappingConfig_.keyboardShurikenMode};
        tap::control::PressCommandMapping m_tardisKeyboardMap{&m_drivers, {&m_tardisCommand}, kMappingConfig_.keyboardTardisMode};
    };//class Robot
}//namspace control
#endif