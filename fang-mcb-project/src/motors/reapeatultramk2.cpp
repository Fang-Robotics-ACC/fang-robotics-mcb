#include "mk2.hpp"

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

    //Torque setters and getters
	void RepeatUltraMk2::setMinSpeed(const MetersPerSecond& minSpeed)
    {
        m_minSpeed = minSpeed;
        
    }

	const MetersPerSecond& RepeatUltraMk2::getMinSpeed() const
    {
        return m_maxSpeed;
    }

	void RepeatUltraMk2::setTorque(const NewtonMeters& torque)
    {
        m_torque = torque;
    }
	const NewtonMeters& RepeatUltraMk2::getTorque() const
    {
        return m_torque;
    }

	void RepeatUltraMk2::setMaxTorque(const NewtonMeters& maxTorque)
    {
        m_maxTorque = maxTorque;
    }
	const NewtonMeters& RepeatUltraMk2::getMaxTorque() const
    {
        return m_maxTorque;
    }

	void RepeatUltraMk2::setMinTorque(const NewtonMeters& minTorque)
    {
        m_minTorque = minTorque;
    }

	const NewtonMeters& RepeatUltraMk2::getMinTorque() const
    {
        return m_minTorque;
    }

}//namespace motors