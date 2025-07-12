#include "gearboxrepeatultramk2.hpp"
namespace motors
{

    GearboxRepeatUltraMk2::GearboxRepeatUltraMk2(tap::Drivers& drivers, const UnifiedProperties& unifiedProperties, const trap::gpio::PwmData& pwmData, bool inverted)
        : GearboxRepeatUltraMk2(drivers, unifiedProperties.controllerInputVoltage,
                                pwmData.pwmPin, pwmData.pinFrequency, unifiedProperties.directionality, inverted, unifiedProperties.gearRatio)
    {}

    GearboxRepeatUltraMk2::GearboxRepeatUltraMk2(tap::Drivers& drivers,
                      const Volts& controllerInputVoltage,
                      tap::gpio::Pwm::Pin pwmPin,
                      const Hertz& pinFrequency,
                      data::motors::Directionality directionality,
                      bool inverted,
                      double gearRatio):
                      RepeatUltraMk2{drivers, controllerInputVoltage, pwmPin, pinFrequency, directionality, inverted},
                      m_gearRatio{gearRatio}
    {}

	void GearboxRepeatUltraMk2::setTargetSpeed(const RPM& speed)
    {
        RepeatUltraMk2::setTargetSpeed(shaftToMotorSpeed(speed));
    }

	RPM GearboxRepeatUltraMk2::getTargetSpeed() const
    {
        return motorToShaftSpeed(RepeatUltraMk2::getTargetSpeed());
    }

	void GearboxRepeatUltraMk2::setMaxSpeed(const RPM& maxSpeed)
    {
        RepeatUltraMk2::setMaxSpeed(shaftToMotorSpeed(maxSpeed));
    }

	RPM GearboxRepeatUltraMk2::getMaxSpeed() const
    {
        return motorToShaftSpeed(RepeatUltraMk2::getMaxSpeed());
    }

	void GearboxRepeatUltraMk2::setMinSpeed(const RPM& minSpeed)
    {
        RepeatUltraMk2::setMinSpeed(shaftToMotorSpeed(minSpeed));
    }

	RPM GearboxRepeatUltraMk2::getMinSpeed() const
    {
        return motorToShaftSpeed(RepeatUltraMk2::getMinSpeed());
    }

    RPM GearboxRepeatUltraMk2::motorToShaftSpeed(const RPM& motorSpeed) const
    {
        //The gear ratio is how many times the motor rotates per gear rotation
        //Therefore the motor speed must be divide by the gear ratio
        return motorSpeed / m_gearRatio;
    }

    RPM GearboxRepeatUltraMk2::shaftToMotorSpeed(const RPM& shaftSpeed) const
    {

        //The gear ratio is how many times the motor rotates per gear rotation
        //Therefore the shaft speed must be multiplied by the gear ratio
        //To figure out how many times to motor rotates
        return shaftSpeed * m_gearRatio;
    }

    double GearboxRepeatUltraMk2::getGearRatio() const
    {
        return m_gearRatio;
    }
}//namespace motors