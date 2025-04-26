#include "repeatultramk2.hpp"

namespace motors
{
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
	void RepeatUltraMk2::setSpeed(const MetersPerSecond& speed)
    {
        m_speed = speed;
    }

	const MetersPerSecond& RepeatUltraMk2::getSpeed() const
    {
        return m_speed;
    }

	void RepeatUltraMk2::setMaxSpeed(const MetersPerSecond& maxSpeed)
    {
        m_maxSpeed = maxSpeed;
    }

	const MetersPerSecond& RepeatUltraMk2::getMaxSpeed() const
    {
        return m_maxSpeed;
    }

	void RepeatUltraMk2::setMinSpeed(const MetersPerSecond& minSpeed)
    {
        m_minSpeed = minSpeed;
        
    }

	const MetersPerSecond& RepeatUltraMk2::getMinSpeed() const
    {
        return m_maxSpeed;
    }

    RepeatUltraMk2::RepeatUltraMk2(tap::Drivers& drivers, tap::gpio::Pwm::Pin pwmPin):
        m_drivers{drivers}, m_pwmPin{pwmPin}
    {}

    void RepeatUltraMk2::setPWM(float dutyCycle)
    {
        m_drivers.pwm.write(dutyCycle, m_pwmPin); 
    }
}//namespace motors