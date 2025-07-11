#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "gearboxrepeatultramk2mock.hpp"
#include "data/directionality.hpp"

#include "drivers.hpp"
#include "unitaliases.hpp"
#include "tap/communication/gpio/pwm.hpp"


using namespace units::literals;

TEST(motorMock, mockTest)
{
    Drivers drivers{};
    mock::motor::GearboxRepeatUltraMk2Mock mockMotor{drivers, 24_V, tap::gpio::Pwm::C1, 500_Hz, data::motor::Directionality::BIDIRECTIONAL, false, 14.0};
    EXPECT_CALL(mockMotor, setTargetSpeed(10_rpm));
    mockMotor.setTargetSpeed(10_rpm);
}