#ifndef FANG_ROBOTICS_MCB_TURRET_MOTION_CONFIG_HPP
#define FANG_ROBOTICS_MCB_TURRET_MOTION_CONFIG_HPP
#include "unitaliases.hpp"
namespace config
{
    namespace motion
    {
        struct TurretConfig 
        {
            RPM maxYawSpeed;
            RPM maxPitchSpeed;
        };
    }
}
#endif