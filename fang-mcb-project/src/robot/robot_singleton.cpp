#include "base_robot.hpp"
#include "robot_singleton.hpp"
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

/**
 * 
 * This is required to not trigger build errors
 * as taproot automatically converts motors to mock motors
 * whose constructors may or may not be as friendly :P
 * 
 * Their oddness causes segmentation faults involving DjiMotorEcoderMock's constructor
 * ON_CALL(*this, isOnline).WillByDefault(testing::Return(true));
 * 
 * TODO: File a bug error (it's 8:08 and I need to start doing chest day) - Rave
 * We should consider making a of taproot, modm, and protothreads to use modules
 * (get access to arm-none-eabi-gcc with C++23)
 * File pull requests all that jazz..
 */

#if defined(ENV_UNIT_TESTS)
    // This is a bit of a HACK: by creating an empty baseRobot
    // in unit tests, it is not expected for any actions to be performed
    // on the BaseRobot anyways
    fang::robot::BaseRobot robot{drivers.commandScheduler, {}, {}};
    fang::robot::IRobot& fang::RobotSingleton::robot{robot};
#elif defined(TARGET_INFANTRY_PIERCE)
    #include "robot/variant/pierce/pierce_config.hpp"
    #include "robot/variant/pierce/pierce.hpp"
    using Robot = fang::robot::Pierce;
    Robot robot{drivers, fang::robot::k_pierceConfig};
    fang::robot::IRobot& fang::RobotSingleton::robot{robot};
#elif defined(TARGET_PIERCE_AUTO_TEST)
    #include "robot/variant/pierce_auto_test/pierce_auto_test.hpp"
    #include "robot/variant/pierce_auto_test/pierce_auto_test_config.hpp"
    using Robot = fang::robot::PierceAutoTest;
    static const Robot::Config& k_robotConfig{fang::robot::k_pierceAutoTestConfig};
    Robot robot{drivers, k_robotConfig};
    RobotSingleton::robot{robot};
#else
    RobotSingleton::robot{robot};
#endif