#include "base_robot.hpp"
#include "robot_singleton.hpp"
#include "driver/drivers_singleton.hpp"

/**
 * Current state of affairs: To support multiple robots without
 * having every possible robot bloating the embedded file size,
 * the robot will be defined in this translation unit.
 * 
 * The previous solution of having the robot configs and the robots defined
 * in different translation units via extern lead to the static order initializatino
 * fiasco. The only clean solution was wrapping those variables in functions which
 * would mean you need these odd wrapper functions for every major section of configuration.
 * 
 * It is desireable to keep the configuration organized into separate files.
 * 
 * You can not just define the static variables, then have a getter function
 * use them because it RELIES on those variables being intialized. This brings
 * back the static order initialization fiasco once more :P 
 * 
 * The solution: Instead of defining the default config into a separate
 * translation unit (which also gets built - another solution is to play
 * with the build settings but that is more cumbersome), the header file will
 * contain a static form of the variable. This means that each robot type
 * will NOT pollute the space.
 * 
 * Other considerations with the nature of the namespaces is that the programmer has to
 * be super careful to keep each name different. This can lead to cumbersome outcomes.
 * 
 * Since static variables have internal linkage, they are not subject to the one definition rule
 * 
 * Other solutions are still being sought out, for now, this is the one that has
 * been chosen over heavy deliberation.
 * 
 * NOTE THAT WE ARE NOT ENCAPSULATING NAMESPACES AS WE ARE INCLUDING FILES.
 * 
 * IF THEY ARE INCLUDED IN THE NAMESPACE, IT WILL LEAD TO A FLURRY OF ERROR
 * MESSAGES AS  STUFF FROM STD OR MODM WILL BE IN FANG::STD OR FANG::MODM AND
 * LOOK FOR JUST STD OR JUST MODM.
 */

// hack: read above. This is a rare instance.
using namespace fang::robot;

 fang::Drivers& drivers{fang::DriversSingleton::getDrivers()};

#if defined(ENV_UNIT_TESTS)
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
     *
     * This is a bit of a HACK: by creating an empty baseRobot
     * in unit tests, it is not expected for any actions to be performed
     * on the BaseRobot anyways
     */
    fang::robot::BaseRobot robot{drivers.commandScheduler, {}, {}};
    fang::robot::IRobot& fang::RobotSingleton::robot{robot};

#elif defined(TARGET_PIERCE)
    #include "robot/variant/pierce/pierce.hpp"
    #include "robot/variant/pierce/pierce_config.hpp"
    using Robot = Pierce;
    Robot pierce{drivers, kPierceConfig};
    fang::robot::IRobot& fang::RobotSingleton::robot{pierce};
#elif defined(TARGET_PIERCE_AUTO_TEST)
    #include "robot/variant/pierce_auto_test/pierce_auto_test.hpp"
    #include "robot/variant/pierce_auto_test/pierce_auto_test_config.hpp"
    using Robot = fang::robot::PierceAutoTest;
    Robot pierceAutoTest{drivers, kPierceAutoTestConfig};
    fang::robot::IRobot& fang::RobotSingleton::robot{pierceAutoTest};

#elif defined(TARGET_SLICE)
    #include "robot/variant/slice/slice.hpp"
    #include "robot/variant/slice/slice_config.hpp"
    using Robot = Slice;
    Robot slice{drivers, kSliceConfig};
    fang::robot::IRobot& fang::RobotSingleton::robot{slice};
#endif


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
}