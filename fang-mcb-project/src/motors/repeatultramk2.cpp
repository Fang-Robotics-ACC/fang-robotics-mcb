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

	Watts RepeatUltraMk2::getWattBudget() const
    {
        return m_wattBudget;
    }

    //Speed setters and getters
	void RepeatUltraMk2::setSpeed(const RPM& speed)
    {
        m_speed = speed;
        const Volts outputVoltage = util::brushless::speedToControllerVoltage(speed, mk_kv);
        //The ratio between the desired output voltage the intput voltage
        //The range of inputs
        const float rawDutyCycle = outputVoltage / mk_controllerInputVoltage;
        const float squeezedDutyCycle = rawDutyCycle / 2.0f;
        const float offset = 0.5f;
        // rawDutyCycle will range between 0 and 1
        // 0.50 will correspond to a 1ms pulse (minimum) assuming the pin is set to a frequency of 2ms
        // 1 will correspond to a 2ms pulse.
        // By dividing the total by 2. It results in the maximum being 0.5
        // Adding the result to 0.5f will shift the minimum to 0.5 and the maximum to 1
        //TODO: Figure out how to use mod::interpolation::Linear
        //TODO: Make this testable
        setPWM(squeezedDutyCycle + offset);
    }

	RPM RepeatUltraMk2::getSpeed() const
    {
        return m_speed;
    }

	void RepeatUltraMk2::setMaxSpeed(const RPM& maxSpeed)
    {
        m_maxSpeed = maxSpeed;
    }

	RPM RepeatUltraMk2::getMaxSpeed() const
    {
        return m_maxSpeed;
    }

	void RepeatUltraMk2::setMinSpeed(const RPM& minSpeed)
    {
        m_minSpeed = minSpeed;
        
    }

	RPM RepeatUltraMk2::getMinSpeed() const
    {
        return m_maxSpeed;
    }

    void RepeatUltraMk2::setPWM(float dutyCycle)
    {
        m_drivers.pwm.write(dutyCycle, m_pwmPin); 
    }

    void RepeatUltraMk2::initialize()
    {
        //Proper timer channel has not been verified
        //m_drivers.pwm.setTimerFrequency(tap::gpio::Pwm::TIMER1, mk_vortexPWMFrequency.to<int>());
    }

	void RepeatUltraMk2::setWattEstimateMode(bool mode)
    {
        m_estimateMode = mode;
    }

	bool RepeatUltraMk2::getWattOverbudgetStatus() const
    {
        return m_overbudgetStatus;
    }

	void RepeatUltraMk2::resetWattOverbudgetStatus()
    {
        m_overbudgetStatus = false;
    }
    Watts RepeatUltraMk2::getWattOverbudgetAmount() const
    {
        return Watts{0};
    }
}//namespace motors