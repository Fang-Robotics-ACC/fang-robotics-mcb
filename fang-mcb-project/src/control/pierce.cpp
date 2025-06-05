#include "pierce.hpp"
#include "drivers.hpp"
#include "configuration/motion_control_config.hpp"

namespace control
{
    Pierce::Pierce(Drivers& drivers)
        :
            m_drivers{drivers},
          m_chassis{drivers, config::chassis::k_defaultConfig},
          m_fieldMecanumCommand{m_chassis, drivers.inputHandler, config::motion::k_defaultMotionConfig}
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
    }
    
    void Pierce::registerSubsystems()
    {
        m_drivers.commandScheduler.registerSubsystem(&m_chassis);
    }
    
    void Pierce::setDefaultCommands()
    {
        m_chassis.setDefaultCommand(&m_fieldMecanumCommand);
    }
    
    void Pierce::registerIoMappings()
    {
    }
}