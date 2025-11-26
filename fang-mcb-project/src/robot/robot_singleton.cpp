#include "base_robot.hpp"
#include "robot_singleton.hpp"
#include "driver/drivers_singleton.hpp"

// These are done so that we don't have to hardcode static instances of every possible robot
#include "robot/variant/pierce/cool_pierce.hpp"
/*
 * Don't add namespace fang so we don't have to have doulbe sets of macros
 *
 */
namespace fang
{

fang::robot::IRobot& fang::RobotSingleton::getRobot()
{
    return robot;
}

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
// LOOK UP STATIC INITIALIZATION ORDER PROBLEM/FIASCO 
// isocpp.org/wiki/faq/ctors#static-init-order-on-first-use
#if defined(ENV_UNIT_TESTS)
    // This is a bit of a HACK: by creating an empty baseRobot
    // in unit tests, it is not expected for any actions to be performed
    // on the BaseRobot anyways
    fang::robot::BaseRobot robot{fang::DriversSingleton::getDrivers().commandScheduler, {}, {}};
    fang::robot::IRobot& fang::RobotSingleton::robot{robot};
#elif defined(TARGET_PIERCE)
    fang::robot::CoolPierce pierce{fang::DriversSingleton::getDrivers()};
    fang::robot::IRobot& fang::RobotSingleton::robot{pierce};
#elif defined(TARGET_PIERCE_AUTO_TEST)
    #include "robot/variant/pierce_auto_test/pierce_auto_test.hpp"
    #include "robot/variant/pierce_auto_test/pierce_auto_test_config.hpp"
    using Robot = fang::robot::PierceAutoTest;
    // TODO: Figure out why if we don't copy the global variable it gives default values
    // this is an issue on the embedded and unit test builds (refer to robot singleton tests)
    static const Robot::Config kRobotConfig{fang::roobot::k_pierceAutoTestConfig};
    static Robot robot{drivers, kRobotConfig};
    RobotSingleton::robot{robot};
#endif
}