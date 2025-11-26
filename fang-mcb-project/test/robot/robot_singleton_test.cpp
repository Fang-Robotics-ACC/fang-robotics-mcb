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
    // TODO: MYSTERY: figure out why we need to copy robot config to prevent zeroing of a global variable???
    using Robot = fang::robot::Pierce;
    const Robot::Config kRobotConfig{fang::robot::k_pierceConfig};
    Robot robot{drivers, kRobotConfig};
}

TEST(RobotSingleton, pierceAutoTestBuild)
{
    using Robot = fang::robot::PierceAutoTest;

    static const Robot::Config& k_robotConfig{fang::robot::k_pierceAutoTestConfig};
    Robot robot{drivers, k_robotConfig};
}
}