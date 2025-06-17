#include "pierce.hpp"

#include "control/robots/pierce/config/chassis_input_config.hpp"
#include "control/robots/pierce/config/turret_motion_config.hpp"
#include "control/robots/pierce/config/turret_config.hpp"

namespace control
{
    extern const Pierce::Config k_config
    {
        k_chassisInputConfig,
        k_turretMotionConfig,
        k_turretConfig
    };
}