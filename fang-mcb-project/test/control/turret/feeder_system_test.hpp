#ifndef FANG_ROBOTICS_MCB_TEST_FLYWHEEL_SYSTEM_TEST_HPP
#define FANG_ROBOTICS_MCB_TEST_FLYWHEEL_SYSTEM_TEST_HPP
#include "drivers.hpp"
#include "control/turret/system/feeder_system.hpp"

namespace test
{
    //Since the classes must mutualy be aware of each other, the delcaration must suffice.
    //I find it better to have the declaration out of the class definition
    class FeederSystemTest;
}
#endif