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
                                                         bool inverted,
                                                         double gearRatio):
    GearboxRepeatUltraMk2(drivers,controllerInputVoltage,
    pwmPin,
    pinFrequency,
    directionality,
    inverted,
    gearRatio)
    {}
    }
}