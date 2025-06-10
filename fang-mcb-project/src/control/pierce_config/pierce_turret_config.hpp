#include "configuration/motion/turret_motion_config.hpp"
#include "unitaliases.hpp"

namespace config
{
    using namespace units::literals;
    namespace pierce 
    {
        const config::motion::TurretConfig k_defaultTurretMotion
        {
            10_rpm,
            10_rpm    
        };
    }
}