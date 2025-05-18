#include "gearboxrepeatultramk2.hpp"
namespace motors
{

    GearboxRepeatUltraMk2::GearboxRepeatUltraMk2(const UnifiedProperties& unifiedProperties, const trap::gpio::PwmData& pwmData, bool inverted)
        : GearboxRepeatUltraMk2(unifiedProperties.drivers, unifiedProperties.controllerInputVoltage,
                                pwmData.pwmPin, pwmData.pinFrequency, unifiedProperties.directionality, inverted, unifiedProperties.gearRatio)
    {}

    GearboxRepeatUltraMk2::GearboxRepeatUltraMk2(tap::Drivers& drivers,
                      const Volts& controllerInputVoltage,
                      tap::gpio::Pwm::Pin pwmPin,
                      const Hertz& pinFrequency,
                      data::motors::Directionality directionality,
                      bool inverted,
                      double gearRatio):
                      m_repeatUltraMk2{drivers, controllerInputVoltage, pwmPin, pinFrequency, directionality, inverted},
                      m_gearRatio{gearRatio}
    {}

	void GearboxRepeatUltraMk2::setSpeed(const RPM& speed)
    {
        m_repeatUltraMk2.setSpeed(shaftToMotorSpeed(speed));
    }

	RPM GearboxRepeatUltraMk2::getSpeed() const
    {
        return motorToShaftSpeed(m_repeatUltraMk2.getSpeed());
    }

	void GearboxRepeatUltraMk2::setMaxSpeed(const RPM& maxSpeed)
    {
        m_repeatUltraMk2.setMaxSpeed(shaftToMotorSpeed(maxSpeed));
    }

	RPM GearboxRepeatUltraMk2::getMaxSpeed() const
    {
        return motorToShaftSpeed(m_repeatUltraMk2.getMaxSpeed());
    }

	void GearboxRepeatUltraMk2::setMinSpeed(const RPM& minSpeed)
    {
        m_repeatUltraMk2.setMinSpeed(shaftToMotorSpeed(minSpeed));
    }

	RPM GearboxRepeatUltraMk2::getMinSpeed() const
    {
        return motorToShaftSpeed(m_repeatUltraMk2.getMinSpeed());
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