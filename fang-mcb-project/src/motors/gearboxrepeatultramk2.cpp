#include "gearboxrepeatultramk2.hpp"
namespace motors
{

    GearboxRepeatUltraMk2::GearboxRepeatUltraMk2(tap::Drivers& drivers,
                      const Volts& controllerInputVoltage,
                      tap::gpio::Pwm::Pin pwmPin,
                      const Hertz& pinFrequency,
                      data::motors::Directionality directionality = data::motors::Directionality::BIDIRECTIONAL,
                      double gearRatio):
                      m_repeatUltraMk2{drivers, controllerInputVoltage, pwmPin, pinFrequency, directionality},
                      m_gearRatio{gearRatio}
    {}

}//namespace motors