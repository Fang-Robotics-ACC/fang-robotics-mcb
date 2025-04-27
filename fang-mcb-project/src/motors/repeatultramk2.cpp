#include "repeatultramk2.hpp"
#include "brushlessutils.hpp"
#include "units.h"

namespace motors
{

    RepeatUltraMk2::RepeatUltraMk2(tap::Drivers& drivers, tap::gpio::Pwm::Pin pwmPin, const Volts& controllerInputVoltage):
        m_drivers{drivers}, m_pwmPin{pwmPin}, mk_controllerInputVoltage {controllerInputVoltage}
    {}

    //Watt budget setters and getters
    void RepeatUltraMk2::setWattBudget(const Watts& wattage)
    {
        m_wattBudget = wattage;
    }

	const Watts& RepeatUltraMk2::getWattBudget() const
    {
        return m_wattBudget;
    }

    //Speed setters and getters
	void RepeatUltraMk2::setSpeed(const RPM& speed)
    {
        m_speed = speed;
        const Volts outputVoltage = util::speedToControllerVoltage(speed, mk_kv);
        //The ratio between the desired output voltage the intput voltage
        const float dutyCycle = outputVoltage / mk_controllerInputVoltage; 
        setPWM(dutyCycle);
    }

	const RPM& RepeatUltraMk2::getSpeed() const
    {
        return m_speed;
    }

	void RepeatUltraMk2::setMaxSpeed(const RPM& maxSpeed)
    {
        m_maxSpeed = maxSpeed;
    }

	const RPM& RepeatUltraMk2::getMaxSpeed() const
    {
        return m_maxSpeed;
    }

	void RepeatUltraMk2::setMinSpeed(const RPM& minSpeed)
    {
        m_minSpeed = minSpeed;
        
    }

	const RPM& RepeatUltraMk2::getMinSpeed() const
    {
        return m_maxSpeed;
    }

    void RepeatUltraMk2::setPWM(float dutyCycle)
    {
        m_drivers.pwm.write(dutyCycle, m_pwmPin); 
    }
}//namespace motors