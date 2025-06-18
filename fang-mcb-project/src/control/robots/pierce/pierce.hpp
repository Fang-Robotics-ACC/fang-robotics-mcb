#ifndef FANG_ROBOTICS_MCB_INFANTRY_HPP
#define FANG_ROBOTICS_MCB_INFANTRY_HPP
#include "drivers.hpp"
#include "control/turret/feeder_subsystem.hpp"
#include "control/turret/ammo_booster_subsystem.hpp"
#include "control/turret/gimbal_subsystem.hpp"

#include "control/turret/turret_input_handler.hpp"
#include "control/robots/pierce/config/chassis_config.hpp"
#include "control/robots/pierce/command_config/field_mecanum_config.hpp"
#include "control/robots/pierce/command_config/shuriken_config.hpp"

#include "control/robots/pierce/config/chassis_input_config.hpp"
#include "control/robots/pierce/config/turret_input_config.hpp"
#include "configuration/motion/turret_motion_config.hpp"


#include "control/chassis/chassis_subsystem.hpp"
#include "control/chassis/field_mecanum_command.hpp"
#include "control/chassis/shuriken_command.hpp"
#include "configuration/chassis_config.hpp"
#include "control/turret/turret_subsystem.hpp"

#include "control/robots/pierce/command_mapping/turret_command_map.hpp"

#include "control/robots/pierce/config/turret_config.hpp"
#include "control/robots/pierce/config/turret_motion_config.hpp"

//Commands
#include "control/turret/command/aim_command.hpp"
#include "control/turret/command/activate_booster_command.hpp"
#include "control/turret/command/autofire_command.hpp"

//Command Maps
#include "control/robots/pierce/command_mapping/turret_command_map.hpp"
#include "control/robots/pierce/command_mapping/chassis_command_map.hpp"

#include "trap/communication/sensors/imu.hpp"

#include "tap/control/press_command_mapping.hpp"

namespace control
{
    /**
     * First Fang: Pierce
     * The first robot in Fang Robotics est. 2025
     */
    class Pierce
    {
    public:
    struct Config
    {
        chassis::ChassisSubsystem::ChassisConfig chassisConfig;
        turret::GimbalSubsystem::Config gimbalConfig;
        turret::FeederSubsystem::Config feederConfig;
        turret::AmmoBoosterSubsystem::Config boosterConfig;
        chassis::ChassisInputHandler::Config chassisInputConfig;
        turret::TurretInputHandler::Config turretInputConfig;
        turret::AimCommand::Config turretMotionConfig;
        chassis::FieldMecanumCommand::Config fieldMecanumConfig;
        chassis::ShurikenCommand::Config shurikenConfig;
    };
        Pierce(Drivers& drivers);
        void initialize();
    private:
        class CommandHandler;
        void initializeSubsystems();
        void setDefaultCommands();
        void registerIoMappings();

        const Config mk_config
        {
            k_chassisConfig,
            k_gimbalSubsystemConfig,
            k_feederConfig,
            k_ammoBoosterConfig,
            k_chassisInputConfig,
            k_turretInputConfig,
            k_turretAimConfig,
            k_fieldMecanumConfig,
            k_shurikenConfig
        };

        config::motion::TurretMotionConfig turretMotionConfig;


        Drivers& m_drivers;

        trap::communication::sensors::Imu m_imu;

        turret::FeederSubsystem m_feeder;
        turret::AmmoBoosterSubsystem m_booster;
        turret::GimbalSubsystem m_gimbal;
        chassis::ChassisSubsystem m_chassis;


        chassis::ChassisInputHandler m_chassisInput;
        turret::TurretInputHandler m_turretInput;

        turret::AimCommand m_aimCommnd{m_gimbal, m_turretInput, mk_config.turretMotionConfig};
        turret::ActivateBoosterCommand m_activateBoosterCommand{m_booster};
        turret::AutofireCommand m_autofireCommand{m_feeder};

        tap::control::PressCommandMapping m_activateBoosterCommandMapping{&m_drivers, {&m_activateBoosterCommand}, k_activateBoosterRemoteState};
        tap::control::PressCommandMapping m_activateAutofireCommandMapping{&m_drivers, {&m_autofireCommand}, k_autofireRemoteState};

        chassis::FieldMecanumCommand m_fieldMecanumCommand{m_chassis, m_gimbal, m_chassisInput, mk_config.fieldMecanumConfig};
        chassis::ShurikenCommand m_shurikenCommand{m_chassis, m_gimbal, m_chassisInput, mk_config.shurikenConfig};

        tap::control::PressCommandMapping m_fieldMecanumCommandMapping{&m_drivers, {&m_fieldMecanumCommand}, k_fieldMecanumRemoteState};
        tap::control::PressCommandMapping m_shurikenCommandMapping{&m_drivers, {&m_shurikenCommand}, k_shurikenModeRemoteState};
    };//class Robot
}//namspace control
#endif
