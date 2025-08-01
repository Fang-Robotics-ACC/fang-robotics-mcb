#include "gearbox_repeat_ultra_mk2.hpp"
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
        RepeatUltraMk2::setTargetSpeed(shaftToMotorSpeed(speed));
    }

    RPM GearboxRepeatUltraMk2::motorToShaftSpeed(const RPM& motorSpeed) const
    {
        //The gear ratio is how many times the motor rotates per gear rotation
        //Therefore the motor speed must be divide by the gear ratio
        return motorSpeed / kGearRatio_;
    }

    RPM GearboxRepeatUltraMk2::shaftToMotorSpeed(const RPM& shaftSpeed) const
    {

        //The gear ratio is how many times the motor rotates per gear rotation
        //Therefore the shaft speed must be multiplied by the gear ratio
        //To figure out how many times to motor rotates
        return shaftSpeed * kGearRatio_;
    }
}//namespace motor