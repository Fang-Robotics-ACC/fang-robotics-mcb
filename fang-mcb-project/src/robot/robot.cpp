#include "robot.hpp"
#include "driver/drivers_singleton.hpp"
/*
 * Don't add namespace fang so we don't have to have doulbe sets of macros
 *
 */

fang::robot::IRobot& fang::RobotSingleton::getRobot()
{
    return robot;
}
// For convenience
fang::Drivers& drivers{fang::DriversSingleton::getDrivers()};

#if defined(TARGET_INFANTRY_PIERCE)
    #include "robot/variant/pierce/pierce_config.hpp"
    #include "robot/variant/pierce/pierce.hpp"
    using Robot = fang::robot::Pierce;
    Robot robot{drivers, fang::robot::k_pierceConfig};
    fang::robot::IRobot& fang::RobotSingleton::robot{robot};
#endif

#if defined(TARGET_PIERCE_AUTO_TEST)
    #include "robot/variant/pierce_auto_test/pierce_auto_test.hpp"
    #include "robot/variant/pierce_auto_test/pierce_auto_test_config.hpp"
    using Robot = fang::robot::PierceAutoTest;
    static const Robot::Config& k_robotConfig{fang::robot::k_pierceAutoTestConfig};
    Robot robot{drivers, k_robotConfig};
    RobotSingleton::robot{robot};
#endif