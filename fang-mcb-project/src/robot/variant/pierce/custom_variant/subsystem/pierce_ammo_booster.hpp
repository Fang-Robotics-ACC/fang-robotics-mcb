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
                makeFlywheels(drivers, config),
                {config.ammoVelocity}
            )
        {
        }
    private:
        /**
         * We cannot copy and std::initializer_list is kinda mid at this
         * So we must do this hack
         */
        static Flywheels makeFlywheels(Drivers& drivers, const Config& config)
        {
            Flywheels flywheels{};
            flywheels.push_back(std::make_unique<Flywheel>(drivers, config.leftFlywheelConfig));
            flywheels.push_back(std::make_unique<Flywheel>(drivers, config.rightFlywheelConfig));
            return flywheels;
        };

    };

}