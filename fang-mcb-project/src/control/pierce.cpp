#include "pierce.hpp"
#include "drivers.hpp"
#include "configuration/motion_control_config.hpp"

namespace control
{
    Pierce::Pierce(Drivers* drivers)
        :
            m_drivers{drivers},
          m_chassis{*drivers, k_config.chassisConfig},
          m_turret{*drivers, k_config.turretConfig},
          m_fieldMecanumCommand{m_chassis, drivers->inputHandler, config::motion::k_defaultMotionConfig},
          m_turretAimCommand{m_turret, drivers->inputHandler.getTurretInputs(), k_config.turretMotionConfig}
    {
    }
    
    void Pierce::initializeSubsystemCommands()
    {
        initializeSubsystems();
        registerSubsystems();
        setDefaultCommands();
        registerIoMappings();
    }
    
    void Pierce::initializeSubsystems()
    {
        m_chassis.initialize();
        m_turret.initialize();
        m_turret.setPitch(0_deg);
    }
    
    void Pierce::registerSubsystems()
    {
        m_drivers->commandScheduler.registerSubsystem(&m_chassis);
        m_drivers->commandScheduler.registerSubsystem(&m_turret);
    }
    
    void Pierce::setDefaultCommands()
    {
        m_chassis.setDefaultCommand(&m_fieldMecanumCommand);
        m_turret.setDefaultCommand(&m_turretAimCommand);
    }
    
    void Pierce::registerIoMappings()
    {
    }
}