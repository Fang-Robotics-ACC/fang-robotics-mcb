#include "gearbox_repeat_ultra_mk2.hpp"
#include "driver/motor/util/gearbox_speed.hpp"

namespace fang::motor
{
    GearboxRepeatUltraMk2::GearboxRepeatUltraMk2
    (
        Drivers& drivers,
        const Config& config
    ):
        RepeatUltraMk2
        (
            drivers,
            RepeatUltraMk2::Config
            {
                config.controllerInputVoltage,
                config.pwmData,
                config.directionality,
                config.inverted
            }
        ),
        kGearRatio_{config.gearRatio}
    {
    }

    GearboxRepeatUltraMk2::GearboxRepeatUltraMk2
    (
        tap::Drivers& drivers, const UnifiedProperties&
        unifiedProperties,
        const trap::gpio::PwmData& pwmData,
        bool inverted
    ):
        GearboxRepeatUltraMk2
        (
            drivers, unifiedProperties.controllerInputVoltage,
            pwmData.pwmPin,
            pwmData.pinFrequency,
            unifiedProperties.directionality,
            inverted,
            unifiedProperties.gearRatio
        )
    {
    }

    GearboxRepeatUltraMk2::GearboxRepeatUltraMk2
    (
        tap::Drivers& drivers,
        const Volts& controllerInputVoltage,
        tap::gpio::Pwm::Pin pwmPin,
        const Hertz& pinFrequency,
        Directionality directionality,
        bool inverted,
        double gearRatio
    ):
        RepeatUltraMk2{drivers, controllerInputVoltage, pwmPin, pinFrequency, directionality, inverted},
        kGearRatio_{gearRatio}
    {
    }

	void GearboxRepeatUltraMk2::setTargetSpeed(const RPM& speed)
    {
        RepeatUltraMk2::setTargetSpeed(shaftToMotorSpeed(speed, kGearRatio_));
    }
}//namespace motor