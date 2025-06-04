#include "repeatultramk2.hpp"
#include "brushlessutils.hpp"
#include "units.h"

#include "trap/communication/pwm_data.hpp"
#include "tap/algorithms/math_user_utils.hpp"

#include <algorithm>
#include <cassert>

using namespace units::literals;

namespace motors
{
    RepeatUltraMk2::RepeatUltraMk2(
        tap::Drivers& drivers,
        const Volts& controllerInputVoltage,
        tap::gpio::Pwm::Pin pwmPin,
        const Hertz& pinFrequency,
        data::motors::Directionality directionality,
        bool inverted)
        :
        m_drivers{drivers}, m_pwmPin{pwmPin},
        mk_controllerInputVoltage{controllerInputVoltage},
        m_inversionMultiplier{inverted && (directionality == data::motors::Directionality::BIDIRECTIONAL)? int8_t{-1}: int8_t{1}},
        m_maxSpeed{mk_maxTheoreticalSpeed},
        m_vortex{drivers.pwm, trap::gpio::PwmData{pwmPin, pinFrequency}, directionality}
    {
        switch(directionality)
        {
        case(data::motors::Directionality::BIDIRECTIONAL):
            m_minSpeed = -m_maxSpeed;
        break;
        case(data::motors::Directionality::UNIDIRECTIONAL):
            m_minSpeed = 0_rpm;
        }
    }

	void RepeatUltraMk2::setSpeed(const RPM& speed)
    {
        const RPM clampedSpeed{tap::algorithms::limitVal<RPM> (speed, m_minSpeed, m_maxSpeed)};
        const double speedPercentage{clampedSpeed * m_inversionMultiplier / mk_maxTheoreticalSpeed};
        m_vortex.setSpeed(speedPercentage);
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
     * The initialization needs to have an arming signal sent for
     * 1-2 seconds. It will be left up to the caller on how to 
     * ensure the delay.
     */
    void RepeatUltraMk2::initialize()
    {
        m_vortex.sendArmingSignal();
    }

}//namespace motors