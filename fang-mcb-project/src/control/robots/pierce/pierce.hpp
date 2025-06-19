#ifndef FANG_ROBOTICS_MCB_INFANTRY_HPP
#define FANG_ROBOTICS_MCB_INFANTRY_HPP
#include "drivers.hpp"
//Subsystems
#include "control/chassis/chassis_subsystem.hpp"

#include "control/turret/gimbal_subsystem.hpp"
#include "control/turret/feeder_subsystem.hpp"
#include "control/turret/ammo_booster_subsystem.hpp"

//Input handlers
#include "control/turret/turret_input_handler.hpp"

#include "control/turret/turret_subsystem.hpp"

//Commands
#include "control/chassis/field_mecanum_command.hpp"
#include "control/chassis/shuriken_command.hpp"

#include "control/turret/command/aim_command.hpp"
#include "control/turret/command/activate_booster_command.hpp"
#include "control/turret/command/autofire_command.hpp"

//Command Maps
#include "control/robots/pierce/command_mapping/turret_command_map.hpp"
#include "control/robots/pierce/command_mapping/chassis_command_map.hpp"

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
        };

        struct Config
        {
            SubsystemConfig subsystemConfig;
            InputConfig inputConfig;
            CommandConfig commandConfig;
        };

        Pierce(Drivers& drivers, const Config& config);
        void initialize();
    private:
        class CommandHandler;
        void initializeSubsystems();
        void setDefaultCommands();
        void registerIoMappings();

        const SubsystemConfig mk_subsystemConfig;
        const InputConfig mk_inputConfig;
        const CommandConfig mk_commandConfig;

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

        tap::control::HoldCommandMapping m_activateBoosterCommandMapping{&m_drivers, {&m_activateBoosterCommand}, k_activateBoosterRemoteState};
        tap::control::HoldCommandMapping m_activateAutofireCommandMapping{&m_drivers, {&m_autofireCommand}, k_autofireRemoteState};

        chassis::FieldMecanumCommand m_fieldMecanumCommand{m_chassis, m_gimbal, m_chassisInput, mk_commandConfig.fieldMecanumConfig};
        chassis::ShurikenCommand m_shurikenCommand{m_chassis, m_gimbal, m_chassisInput, mk_commandConfig.shurikenConfig};

        tap::control::PressCommandMapping m_fieldMecanumCommandMapping{&m_drivers, {&m_fieldMecanumCommand}, k_fieldMecanumRemoteState};
        tap::control::PressCommandMapping m_shurikenCommandMapping{&m_drivers, {&m_shurikenCommand}, k_shurikenModeRemoteState};
    };//class Robot
}//namspace control
#endif
