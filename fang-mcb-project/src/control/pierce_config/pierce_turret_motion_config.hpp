#ifndef FANG_ROBOTICS_MCB_PIERCE_TURRET_MOTION_CONFIG_HPP
#define FANG_ROBOTICS_MCB_PIERCE_TURRET_MOTION_CONFIG_HPP
#include "configuration/motion/turret_motion_config.hpp"
#include "unitaliases.hpp"
namespace control
{
    namespace pierceConfig
    {
        using namespace units::literals;
        static constexpr config::motion::TurretConfig k_turretMotionConfig
        {
            10_rpm,
            10_rpm
        };
    }
}
#endif