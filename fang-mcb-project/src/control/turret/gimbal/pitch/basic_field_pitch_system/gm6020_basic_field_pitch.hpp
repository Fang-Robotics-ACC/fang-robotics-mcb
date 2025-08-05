#pragma once

#include "basic_field_pitch_system.hpp"
#include "driver/drivers.hpp"
#include "wrap/trap/motor/dji_gm6020.hpp"

namespace fang::turret
{
    class GM6020BasicFieldPitch : public BasicFieldPitchSystem
    {
    public:
        using Motor = trap::motor::DjiGM6020;
        struct Config
        {
            Motor::Config motorConfig;
            BasicFieldPitchSystem::Config pitchSystemConfig;
        };
        GM6020BasicFieldPitch(Drivers& drivers, const Config& config):
            BasicFieldPitchSystem
            {
                std::make_unique<Motor>(drivers, config.motorConfig),
                config.pitchSystemConfig
            }
        {}
    };
}