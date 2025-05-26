#include "pierce.hpp"
#include "drivers.hpp"

namespace control
{
    Pierce::Pierce(Drivers& drivers)
        : m_drivers{drivers},
          m_chassis{drivers, mk_config.chassisConfig},
          m_fieldMecanumCommand{m_chassis, drivers.inputHandler}
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