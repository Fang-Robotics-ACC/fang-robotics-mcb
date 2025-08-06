#include "pierce.hpp"
#include "driver/drivers.hpp"
#include "modm/platform/core/delay_impl.hpp"


namespace fang::robot 
{
    Pierce::Pierce(Drivers& drivers, const Config& config):
        BaseRobot{makeRobot(drivers, config)}
    {}
}