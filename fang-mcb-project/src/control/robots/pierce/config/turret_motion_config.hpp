#ifndef FANG_ROBOTICS_MCB_TURRET_MOTION_CONFIG_HPP
#define FANG_ROBOTICS_MCB_TURRET_MOTION_CONFIG_HPP
#include "configuration/motion/turret_motion_config.hpp"
#include "unitaliases.hpp"
namespace control
{
    using namespace units::literals;
    static const config::motion::TurretMotionConfig k_turretMotionConfig
    {
        40_rpm,
        120_rpm
    };
}
#endif