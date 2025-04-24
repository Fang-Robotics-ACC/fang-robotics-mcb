#include "mk2.hpp"

namespace motors
{

    //Watt budget setters and getters
    void MK2::setWattBudget(const Watts& wattage)
    {
        m_wattBudget = wattage;
    }

	const Watts& MK2::getWattBudget() const
    {
        return m_wattBudget;
    }

    //Speed setters and getters
	void MK2::setSpeed(const MetersPerSecond& speed)
    {
        m_speed = speed;
    }

	const MetersPerSecond& MK2::getSpeed() const
    {
        return m_speed;
    }

	void MK2::setMaxSpeed(const MetersPerSecond& maxSpeed)
    {
        m_maxSpeed = maxSpeed;
    }

	const MetersPerSecond& MK2::getMaxSpeed() const
    {
        return m_maxSpeed;
    }

    //Torque setters and getters
	void MK2::setMinSpeed(const MetersPerSecond& minSpeed)
    {
        m_minSpeed = minSpeed;
        
    }

	const MetersPerSecond& MK2::getMinSpeed() const
    {
        return m_maxSpeed;
    }

	void MK2::setTorque(const NewtonMeters& torque)
    {
        m_torque = torque;
    }
	const NewtonMeters& MK2::getTorque() const
    {
        return m_torque;
    }

	void MK2::setMaxTorque(const NewtonMeters& maxTorque)
    {
        m_maxTorque = maxTorque;
    }
	const NewtonMeters& MK2::getMaxTorque() const
    {
        return m_maxTorque;
    }

	void MK2::setMinTorque(const NewtonMeters& minTorque)
    {
        m_minTorque = minTorque;
    }

	const NewtonMeters& MK2::getMinTorque() const
    {
        return m_minTorque;
    }

}//namespace motors