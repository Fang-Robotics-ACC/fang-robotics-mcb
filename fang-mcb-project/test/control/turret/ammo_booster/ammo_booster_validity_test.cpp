#include "robot/variant/pierce/custom_variant/subsystem/pierce_ammo_booster.hpp"
#include "robot/variant/pierce/config/subsystem/ammo_booster_config.hpp"
#include <gtest/gtest.h>

namespace fang::turret
{
    TEST(PierceAmmoBooster, validity)
    {
        //Check for memory errors and whatnot
        Drivers drivers{};
        PierceAmmoBooster booster{drivers, robot::kAmmoBoosterConfig};
        booster.initialize();
        booster.boostOff();
        booster.boostOn();
        booster.update();
        booster.refresh();
    }
}