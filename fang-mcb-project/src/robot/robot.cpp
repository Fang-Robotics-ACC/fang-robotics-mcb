#include "robot.hpp"
#include "driver/drivers_singleton.hpp"

namespace fang
{
    robot::IRobot& RobotSingleton::getRobot()
    {
        return robot;
    }
    // For convenience
    Drivers& drivers{DriversSingleton::getDrivers()};

#if defined(TARGET_INFANTRY_PIERCE)
    #include "robot/variant/pierce/pierce_config.hpp"
    #include "robot/variant/pierce/pierce.hpp"
    using Robot = fang::robot::Pierce;
    static const Robot::Config& k_robotConfig{fang::robot::k_pierceConfig};
    Robot robot{drivers, k_robotConfig};
    RobotSingleton::robot{robot};
#endif

#if defined(TARGET_PIERCE_AUTO_TEST)
    #include "robot/variant/pierce_auto_test/pierce_auto_test.hpp"
    #include "robot/variant/pierce_auto_test/pierce_auto_test_config.hpp"
    using Robot = fang::robot::PierceAutoTest;
    static const Robot::Config& k_robotConfig{fang::robot::k_pierceAutoTestConfig};
    Robot robot{drivers, k_robotConfig};
    RobotSingleton::robot{robot};
#endif
}