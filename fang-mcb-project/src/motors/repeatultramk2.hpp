#ifndef MK2_MOTORS_HPP_ASFEFKLSJKDFJSAEFE
#define MK2_MOTORS_HPP_ASFEFKLSJKDFJSAEFE
#include "idcmotor.h"
#include "iwattbudgeter.h"
#include "units.h"

#include "tap/drivers.hpp"
#include "tap/communication/gpio/pwm.hpp"
#include "unitaliases.hpp"
#include "vortex80aesclogic.hpp"
#include "data/directionality.hpp"
#include "units.h"

namespace motors
{
    /*!
    RPM is positive according to the right hand rule when the motor is the shaft pointing up. This is the the gearbox detached!!!
    */
    class RepeatUltraMk2 : virtual public rail::ISpeedMotor<RPM>
    {
    public:
        RepeatUltraMk2(tap::Drivers& drivers,
                      const Volts& controllerInputVoltage,
                      tap::gpio::Pwm::Pin pwmPin,
                      const Hertz& pinFrequency,
                      data::motors::Directionality directionality = data::motors::Directionality::BIDIRECTIONAL);

		void setSpeed(const RPM& speed) override;
		RPM getSpeed() const override;

		void setMaxSpeed(const RPM& maxSpeed) override;
		RPM getMaxSpeed() const override;
		void setMinSpeed(const RPM& minSpeed) override;
		RPM getMinSpeed() const override;
    private:

        const RPM mk_maxTheoreticalSpeed;
        RPM m_speed{0};
        RPM m_maxSpeed{0};
        RPM m_minSpeed{0};
        tap::Drivers& m_drivers;
        tap::gpio::Pwm::Pin m_pwmPin;
        const Volts mk_controllerInputVoltage;
        // This was the Repeat Robotics provided value for the ratio between the rpm and the voltage associated with i
        const RPMPerVolt mk_kv{1450.0};

        logic::motors::Vortex80AEscLogic m_vortexLogic;

        /*!
            PWM should be between 0 and 1
            The motor is assumed to be in a bidirectional setup
            Therefore the if the pwm is 0.5 the motor should be still.
        */
        void setPWM(float dutyCycle);
        void initialize();
   };
}
#endif 