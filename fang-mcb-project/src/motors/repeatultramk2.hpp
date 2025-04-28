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
    /*!
    RPM is positive according to the right hand rule when the motor is the shaft pointing up. This is the the gearbox detached!!!
    */
    class RepeatUltraMk2 : virtual public rail::ISpeedMotor<RPM, Watts>, virtual public rail::IWattBudgeter<Watts>
    {
    public:
        RepeatUltraMk2(tap::Drivers& drivers, tap::gpio::Pwm::Pin pwmPin, const Volts& controllerInputVoltage);

        /// @brief Does not limit anything yet
        /// @param wattage 
        void setWattBudget(const Watts& wattage) override;

        /// Does not limit anything yet
		const Watts& getWattBudget() const override;

		void setSpeed(const RPM& speed) override;
		const RPM& getSpeed() const override;

		void setMaxSpeed(const RPM& maxSpeed) override;
		const RPM& getMaxSpeed() const override;
		void setMinSpeed(const RPM& minSpeed) override;
		const RPM& getMinSpeed() const override;


    private:
        Watts m_wattBudget{0};
        Watts m_maxWattBudget{0};
        Watts m_minWattBudget{0};

        RPM m_speed{0};
        RPM m_maxSpeed{0};
        RPM m_minSpeed{0};
        tap::Drivers& m_drivers;
        tap::gpio::Pwm::Pin m_pwmPin;
        const Volts mk_controllerInputVoltage;
        // This was the Repeat Robotics provided value for the ratio between the rpm and the voltage associated with i
        const RPMPerVolt mk_kv{1450.0};

        /*!
            PWM should be between 0 and 1
            The motor is assumed to be in a bidirectional setup
            Therefore the if the pwm is 0.5 the motor should be still.
        */
        void setPWM(float dutyCycle);
        /*!
        This provides the speed that the motor will output to achieve the
        given output voltage from the controller.*/
        const RPM& controllerVoltageToSpeed(const Volts& volts);
        /*!
        This provides the voltage that the controller will output to achieve the
        given speed on the motor.*/
        const Volts& speedToControllerVoltage(const RPM& speed);
   };
}
#endif 