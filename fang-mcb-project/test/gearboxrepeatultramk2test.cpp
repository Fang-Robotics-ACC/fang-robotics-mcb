#include "gtest/gtest.h"
#include "gearboxrepeatultramk2.hpp"
#include "directionality.hpp"
#include "unitaliases.hpp"
#include "tap/drivers.hpp"
#include "tap/communication/gpio/pwm.hpp"

using namespace units::literals;
TEST(minSpeedTest, repeatUltraMk2)
{
    constexpr Volts controllerVoltage{24};
    constexpr Hertz frequency{500};
    constexpr double gearRatio{14.0};

    
    tap::Drivers drivers{};
    motors::GearboxRepeatUltraMk2 motor{drivers, controllerVoltage, tap::gpio::Pwm::C1, frequency, data::motors::Directionality::UNIDIRECTIONAL, gearRatio};
    motor.setSpeed(0_rpm);
    drivers.pwm.write(0.0, tap::gpio::Pwm::C1);

    EXPECT_CALL(drivers.pwm,write);
}