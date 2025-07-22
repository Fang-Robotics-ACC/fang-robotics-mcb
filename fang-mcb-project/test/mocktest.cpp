#include "wrap/units/units_alias.hpp"

#include "test/mock/motor/gearboxrepeatultramk2mock.hpp"

#include "drivers.hpp"
#include "tap/communication/gpio/pwm.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace units::literals;

TEST(motorMock, mockTest)
{
    Drivers drivers{};
    mock::motor::GearboxRepeatUltraMk2Mock mockMotor{drivers, 24_V, tap::gpio::Pwm::C1, 500_Hz, motor::Directionality::BIDIRECTIONAL, false, 14.0};
    EXPECT_CALL(mockMotor, setTargetSpeed(10_rpm));
    mockMotor.setTargetSpeed(10_rpm);
}