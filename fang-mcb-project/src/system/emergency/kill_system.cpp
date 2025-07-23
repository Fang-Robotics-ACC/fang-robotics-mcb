#include "kill_system.hpp"
#include "driver/drivers_singleton.hpp"
namespace fang::emergency
{
    void killSystem()
    {
        DriversSingleton::getDrivers().kill();
    }
}