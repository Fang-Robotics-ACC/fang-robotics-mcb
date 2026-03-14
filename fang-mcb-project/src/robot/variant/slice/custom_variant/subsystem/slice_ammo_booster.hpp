#pragma once

#include "control/turret/ammo_booster/simple_ammo_booster_subsystem/simple_ammo_booster/simple_ammo_booster.hpp"
#include "control/turret/flywheel/basic_flywheel/m3508_basic_flywheel.hpp"
#include "util/stl/make_vector_with_moved_list.hpp"

#include "driver/drivers.hpp"

namespace fang::turret
{
    class SliceAmmoBooster : public SimpleAmmoBooster
    {
    public:
        using Flywheel = M3508BasicFlywheel;

        struct Config
        {
            MetersPerSecond ammoVelocity;
            Flywheel::Config leftFlywheelConfig;
            Flywheel::Config rightFlywheelConfig;
        };

        SliceAmmoBooster(Drivers& drivers, const Config& config):
            SimpleAmmoBooster
            (
                drivers,
                // Note that SimpleAmmoBooster::Flywheel is the generic type in parent class while Flyhweel
                // is the specific type use for PierceAmmoBooster
                stl::makeVectorWithMovedList<std::unique_ptr<SimpleAmmoBooster::Flywheel>>(
                    std::make_unique<Flywheel>(drivers, config.leftFlywheelConfig),
                    std::make_unique<Flywheel>(drivers, config.rightFlywheelConfig)
                ),
                {config.ammoVelocity}
            )
        {
        }
    };
}