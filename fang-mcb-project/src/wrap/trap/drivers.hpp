#ifndef FANG_ROBOTICS_MCB_TRAP_DRIVERS_HPP
#define FANG_ROBOTICS_MCB_TRAP_DRIVERS_HPP
#include "tap/drivers.hpp"
namespace trap
{
    //Use generic taproot drivers because most classes are only reliant upon it
    //This allows code to be used across differen code bases as most drivers classes
    //Will be inherited from tap::Drivers
    //TODO: Give enhanced option for current drivers which has init() and whatnot
    //Although this will require to adapt to different imu
    using Drivers = tap::Drivers;
}
#endif