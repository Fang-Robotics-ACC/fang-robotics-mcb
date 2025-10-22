#pragma once

#include "basic_field_pitch_system.hpp"
#include "driver/drivers.hpp"
#include "driver/motor/pid/dual_cascade_position/dual_cascade_gm6020.hpp"

namespace fang::turret
{
    class GM6020CascadeFieldPitch : public BasicFieldPitchSystem
    {
    public:
        using Motor = motor::DualCascadeGm6020;
        struct Config
        {
            Motor::Config motorConfig;
            BasicFieldPitchSystem::Config pitchSystemConfig;
        };
        GM6020CascadeFieldPitch(Drivers& drivers, const Config& config):
            BasicFieldPitchSystem 
            {
                std::make_unique<Motor>(drivers, config.motorConfig),
                config.pitchSystemConfig
            }
        {}
    };
}