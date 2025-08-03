#pragma once

#include "basic_flywheel.hpp"
#include "driver/drivers.hpp"
#include "wrap/trap/motor/dji_m3508.hpp"

namespace fang::turret
{
    class M3508BasicFlywheel : public BasicFlywheel
    {
    public:
        using Motor = trap::motor::DjiM3508;
        struct Config
        {
            Motor::Config motorConfig;
            BasicFlywheel::Config flywheelConfig;
        };

        M3508BasicFlywheel(Drivers& drivers, const Config& config):
            BasicFlywheel
            (
                std::make_unique<Motor>(config.motorConfig),
                config.flywheelConfig
            )
        {}

    };
}