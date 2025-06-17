#ifndef FANG_ROBOTICS_MCB_INFANTRY_HPP
#define FANG_ROBOTICS_MCB_INFANTRY_HPP
#include "drivers.hpp"

#include "control/robots/pierce/config/chassis_input_config.hpp"
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
#include "control/turret/command/deactivate_booster_command.hpp"
#include "control/turret/command/autofire_command.hpp"
#include "control/turret/command/stop_autofire_command.hpp"

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
        chassis::ChassisInputHandler::Config chassisInputConfig;
        config::motion::TurretMotionConfig turretMotionConfig;
        turret::TurretSubsystem::Config turretConfig;
    };
        Pierce(Drivers& drivers);
        void initialize();
    private:
        void initializeSubsystems();
        void registerSubsystems();
        void setDefaultCommands();
        void registerIoMappings();

        const Config mk_config
        {
            k_chassisInputConfig,
            k_turretMotionConfig,
            k_turretConfig
        };

        config::motion::TurretMotionConfig turretMotionConfig;


        Drivers& m_drivers;

        chassis::ChassisInputHandler m_chassisInput;

        trap::communication::sensors::Imu m_imu;

        turret::TurretSubsystem m_turret;

        turret::AimCommand m_aimCommnd;
        turret::ActivateBoosterCommand m_activateBoosterCommand;
        turret::DeactivateBoosterCommand m_deactivateBoosterCommand;
        turret::AutofireCommand m_autofireCommand;
        turret::StopAutofireCommand m_stopAutofireCommand;

        tap::control::PressCommandMapping m_activateBoosterCommandMapping{&m_drivers, {&m_activateBoosterCommand}, k_activateBoosterRemoteState};
        tap::control::PressCommandMapping m_deactivateBoosterCommandMapping{&m_drivers, {&m_deactivateBoosterCommand}, k_deactivateBoosterRemoteState};
        tap::control::PressCommandMapping m_activateAutofireCommandMapping{&m_drivers, {&m_autofireCommand}, k_autofireRemoteState};
        tap::control::PressCommandMapping m_stopAutofireCommandMapping{&m_drivers, {&m_stopAutofireCommand}, k_stopAutofireRemoteState};

        chassis::ChassisSubsystem m_chassis;
        chassis::FieldMecanumCommand m_fieldMecanumCommand;
        chassis::ShurikenCommand m_shurikenCommand;

        tap::control::PressCommandMapping m_fieldMecanumCommandMapping{&m_drivers, {&m_fieldMecanumCommand}, k_fieldMecanumRemoteState};
        tap::control::PressCommandMapping m_shurikenCommandMapping{&m_drivers, {&m_shurikenCommand}, k_shurikenModeRemoteState};
    };//class Robot
}//namspace control
#endif
