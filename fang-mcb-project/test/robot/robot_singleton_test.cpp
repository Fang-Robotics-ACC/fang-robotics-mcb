#include <gtest/gtest.h>
#include "robot/variant/pierce/pierce_config.hpp"
#include "robot/variant/pierce/pierce.hpp"

#include "robot/variant/pierce_auto_test/pierce_auto_test.hpp"
#include "robot/variant/pierce_auto_test/pierce_auto_test_config.hpp"

#include "driver/drivers_singleton.hpp"

namespace robotSingletonTest
{
fang::Drivers& drivers{fang::DriversSingleton::getDrivers()};

TEST(RobotSingleton, pierceBuild)
{
    using Robot = fang::robot::Pierce;
    Robot robot{drivers,fang::robot::getPierceConfig()};
}

TEST(RobotSingleton, pierceAutoTestBuild)
{
    using Robot = fang::robot::PierceAutoTest;
    Robot robot{drivers,fang::robot::getPierceAutoTestConfig()};
}
}