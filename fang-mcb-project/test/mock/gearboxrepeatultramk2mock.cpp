#include "gearboxrepeatultramk2mock.hpp"
namespace mock
{
    namespace motors
    {
    GearboxRepeatUltraMk2Mock::GearboxRepeatUltraMk2Mock(tap::Drivers& drivers,
                                                         const Volts& controllerInputVoltage,
                                                         tap::gpio::Pwm::Pin pwmPin,
                                                         const Hertz& pinFrequency,
                                                         data::motors::Directionality directionality,
                                                         double gearRatio):
    GearboxRepeatUltraMk2(drivers,controllerInputVoltage,
    pwmPin,
    pinFrequency,
    directionality,
    gearRatio)
    {}
    }
}