#include "pierce.hpp"
#include "drivers.hpp"
#include "configuration/motion_control_config.hpp"


namespace control
{
    Pierce::Pierce(Drivers& drivers)
        :
            m_drivers{drivers},
            m_turret{drivers, k_turretConfig},
            m_aimCommnd{m_turret, drivers.inputHandler.getTurretInputs(), mk_config.turretMotionConfig}
            //m_chassis{drivers, config::chassis::k_defaultConfig},
            //m_fieldMecanumCommand{m_chassis, drivers.inputHandler, config::motion::k_defaultMotionConfig}
    {
    }
    
    void Pierce::initialize()
    {
        initializeSubsystems();
        //registerSubsystems();
        setDefaultCommands();
        //registerIoMappings();
    }
    
    void Pierce::initializeSubsystems()
    {
        m_turret.registerAndInitialize();
    }
    
    void Pierce::registerSubsystems()
    {
        //m_drivers.commandScheduler.registerSubsystem(&m_chassis);
    }
    
    void Pierce::setDefaultCommands()
    {
        m_turret.setDefaultCommand(&m_aimCommnd);
        //m_chassis.setDefaultCommand(&m_fieldMecanumCommand);
    }
    
    void Pierce::registerIoMappings()
    {
    }
}