#include "flywheel_system.hpp"

namespace control
{
    namespace turret
    {
        FlywheelSystem::FlywheelSystem(Drivers& drivers, const Config& config)
        :   m_motor{drivers, config.motorConfig}
        {
        }
    }
}