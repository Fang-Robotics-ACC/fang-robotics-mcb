#include "repeatultramk2.hpp"
#include "brushlessutils.hpp"
#include "units.h"

#include "trap/communication/pwm_data.hpp"

#include <algorithm>
#include <cassert>

using namespace units::literals;

namespace motors
{
    RepeatUltraMk2::RepeatUltraMk2(tap::Drivers& drivers,
                      const Volts& controllerInputVoltage,
                      tap::gpio::Pwm::Pin pwmPin,
                      const Hertz& pinFrequency,
                      data::motors::Directionality directionality,
                      bool inverted):
                      m_drivers{drivers}, m_pwmPin{pwmPin},
                      mk_controllerInputVoltage{controllerInputVoltage},
                      m_inversionMultiplier{inverted && (directionality == data::motors::Directionality::BIDIRECTIONAL)? int8_t{-1}: int8_t{1}},
                      m_vortexLogic{drivers.pwm, trap::gpio::PwmData{pwmPin, pinFrequency}, directionality}
    {
        switch(directionality)
        {
        case(data::motors::Directionality::BIDIRECTIONAL):
            m_minSpeed = -mk_maxTheoreticalSpeed;
        break;
        case(data::motors::Directionality::UNIDIRECTIONAL):
            m_minSpeed = 0_rpm;
        }
    }

	void RepeatUltraMk2::setSpeed(const RPM& speed)
    {
        const RPM clampedSpeed{std::clamp<RPM>(speed * m_inversionMultiplier, m_minSpeed, m_maxSpeed)};
        const double rangePercentage{clampedSpeed / mk_maxTheoreticalSpeed};
        setPWM(m_vortexLogic.calculateDutyCycle(rangePercentage));
    }

	RPM RepeatUltraMk2::getSpeed() const
    {
        return m_speed;
    }

	void RepeatUltraMk2::setMaxSpeed(const RPM& maxSpeed)
    {
        m_maxSpeed = maxSpeed;
        setSpeed(getSpeed());
    }

	RPM RepeatUltraMk2::getMaxSpeed() const
    {
        return m_maxSpeed;
    }

	void RepeatUltraMk2::setMinSpeed(const RPM& minSpeed)
    {
        m_minSpeed = minSpeed;
        setSpeed(getSpeed()); 
    }

	RPM RepeatUltraMk2::getMinSpeed() const
    {
        return m_minSpeed;
    }

    void RepeatUltraMk2::setPWM(float dutyCycle)
    {
        m_drivers.pwm.write(dutyCycle, m_pwmPin); 
    }

    /**
     * The initialization needs to have a 0 signal sent for
     * 1-2 seconds. It will be left up to the caller on how to 
     * ensure the delay.
     */
    void RepeatUltraMk2::initialize()
    {
        setSpeed(0_rpm);
    }

}//namespace motors