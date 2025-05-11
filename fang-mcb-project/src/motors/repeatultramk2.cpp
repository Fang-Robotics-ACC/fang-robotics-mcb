#include "repeatultramk2.hpp"
#include "brushlessutils.hpp"
#include "units.h"

#include <cassert>

namespace motors
{

    RepeatUltraMk2::RepeatUltraMk2(tap::Drivers& drivers,
                      const Volts& controllerInputVoltage,
                      tap::gpio::Pwm::Pin pwmPin,
                      const Hertz& pinFrequency,
                      data::motors::Directionality directionality):
                      m_drivers{drivers}, m_pwmPin{pwmPin},
                      mk_controllerInputVoltage{controllerInputVoltage},
                      m_vortexLogic{directionality, pinFrequency},
                      mk_maxTheoreticalSpeed{controllerInputVoltage * mk_kv}
    {}

	void RepeatUltraMk2::setSpeed(const RPM& speed)
    {
        const double rangePercentage{speed / mk_maxTheoreticalSpeed};
        assert(-1.0 < rangePercentage && rangePercentage < 1.0 && "Precentage out off bounds");
        setPWM(m_vortexLogic.calculateDutyCycle(rangePercentage));
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

}//namespace motors