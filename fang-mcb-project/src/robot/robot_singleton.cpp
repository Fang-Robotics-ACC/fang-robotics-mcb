#include "base_robot.hpp"
#include "robot_singleton.hpp"
#include "driver/drivers_singleton.hpp"

// These are done so that we don't have to hardcode static instances of every possible robot
#include "robot/variant/pierce/cool_pierce.hpp"
#include "robot/variant/pierce_auto_test/cool_pierce_auto_test.hpp"

/*
 * Don't add namespace fang so we don't have to have doulbe sets of macros
 *
 */
namespace fang
{

robot::IRobot& fang::RobotSingleton::getRobot()
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
    static robot::BaseRobot theRobot{DriversSingleton::getDrivers().commandScheduler, {}, {}};
    robot::IRobot& RobotSingleton::robot{theRobot};
#elif defined(TARGET_PIERCE)
    robot::CoolPierce pierce{fang::DriversSingleton::getDrivers()};
    robot::IRobot& fang::RobotSingleton::robot{pierce};
#elif defined(TARGET_PIERCE_AUTO_TEST)
    robot::CoolPierceAutoTest pierceAutoTest{DriversSingleton::getDrivers()};
    robot::IRobot& RobotSingleton::robot{pierceAutoTest};
#endif
}