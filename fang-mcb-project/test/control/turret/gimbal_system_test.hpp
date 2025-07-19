#ifndef FANG_ROBOTICS_MCB_TEST_GIMBAL_SYSTEM_TEST_HPP
#define FANG_ROBOTICS_MCB_TEST_GIMBAL_SYSTEM_TEST_HPP
#include "control/turret/system/gimbal_system.hpp"
#include "driver/drivers.hpp"

namespace test
{
    //Since the classes must mutualy be aware of each other, the delcaration must suffice.
    //I find it better to have the declaration out of the class definition
    class GimbalSystemTest;
}
#endif