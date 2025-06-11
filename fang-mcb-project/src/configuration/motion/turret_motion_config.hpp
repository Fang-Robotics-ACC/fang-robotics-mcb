#ifndef FANG_ROBOTICS_MCB_MOTION_TURRET_CONFIG_HPP
#define FANG_ROBOTICS_MCB_MOTION_TURRET_CONFIG_HPP
#include "unitaliases.hpp"

namespace config
{
    namespace motion
    {
        struct TurretMotionConfig
        {
            RPM pitchSpeed;
            RPM yawSpeed;

        };

    }
}
#endif