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
    }
    
    void Pierce::initializeSubsystems()
    {
    }
    
    void Pierce::registerSubsystems()
    {
    }
    
    void Pierce::setDefaultCommands()
    {
    }
    
    void Pierce::registerIoMappings()
    {
    }
}