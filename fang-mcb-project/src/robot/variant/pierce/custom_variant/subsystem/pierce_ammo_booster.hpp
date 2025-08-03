#pragma once

#include "control/turret/ammo_booster/simple_ammo_booster_subsystem/simple_ammo_booster/simple_ammo_booster.hpp"
#include "control/turret/flywheel/basic_flywheel/m3508_basic_flywheel.hpp"

#include "driver/drivers.hpp"

namespace fang::turret
{
    class PierceAmmoBooster : public SimpleAmmoBooster
    {
    public:
        using Flywheel = M3508BasicFlywheel;

        struct Config
        {
            MetersPerSecond ammoVelocity;
            Flywheel::Config leftFlywheelConfig;
            Flywheel::Config rightFlywheelConfig;
        };

        PierceAmmoBooster(Drivers& drivers, const Config& config):
            SimpleAmmoBooster
            (
                drivers,
                Flywheels
                {
                    std::make_unique<Flywheel>(config.leftFlywheelConfig),
                    std::make_unique<Flywheel>(config.rightFlywheelConfig)
                },
                {config.ammoVelocity}
            )

        {
        }

    };

}