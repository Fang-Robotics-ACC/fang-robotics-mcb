#ifndef MK2_MOTORS_HPP_ASFEFKLSJKDFJSAEFE
#define MK2_MOTORS_HPP_ASFEFKLSJKDFJSAEFE
#include "idcmotor.h"
#include "iwattbudgeter.h"
#include "units.h"

#include "tap/drivers.hpp"
#include "tap/communication/gpio/pwm.hpp"
#include "unitaliases.hpp"

namespace motors
{
    class RepeatUltraMk2 : virtual public rail::ISpeedMotor<MetersPerSecond, Watts>, virtual public rail::IWattBudgeter<Watts>
    {
    public:
        RepeatUltraMk2(tap::Drivers& drivers, tap::gpio::Pwm::Pin pwmPin);

        void setWattBudget(const Watts& wattage) override;
		const Watts& getWattBudget() const override;

		void setSpeed(const MetersPerSecond& speed) override;
		const MetersPerSecond& getSpeed() const override;

		void setMaxSpeed(const MetersPerSecond& maxSpeed) override;
		const MetersPerSecond& getMaxSpeed() const override;
		void setMinSpeed(const MetersPerSecond& minSpeed) override;
		const MetersPerSecond& getMinSpeed() const override;

    private:
        Watts m_wattBudget{0};
        Watts m_maxWattBudget{0};
        Watts m_minWattBudget{0};

        MetersPerSecond m_speed{0};
        MetersPerSecond m_maxSpeed{0};
        MetersPerSecond m_minSpeed{0};
        tap::Drivers& m_drivers;
        const tap::gpio::Pwm::Pin m_pwmPin;

        /*!
            PWM should be between 0 and 1
            The motor is assumed to be in a bidirectional setup
            Therefore the if the pwm is 0.5 the motor should be still.
        */
        void setPWM(float dutyCycle);
   };
}
#endif 