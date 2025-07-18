#ifndef FANG_ROBOTICS_MCB_MOTORS_REPEAT_ULTRA_MK2_HPP
#define FANG_ROBOTICS_MCB_MOTORS_REPEAT_ULTRA_MK2_HPP
#include "data/directionality.hpp"
#include "vortex80aesc.hpp"
#include "wrap/rail/rail_motors.hpp"
#include "wrap/units/units_alias.hpp"

#include "trap/algorithms/ramp.hpp"

#include "tap/drivers.hpp"
#include "tap/communication/gpio/pwm.hpp"

namespace motor
{
    /*!
    RPM is positive according to the right hand rule when the motor is the shaft pointing up. This is the the gearbox detached!!!
    */
    class RepeatUltraMk2 : public virtual ISpeedMotor
    {
    public:
        RepeatUltraMk2(tap::Drivers& drivers,
                      const Volts& controllerInputVoltage,
                      tap::gpio::Pwm::Pin pwmPin,
                      const Hertz& pinFrequency,
                      Directionality directionality,
                      bool inverted = false);

        /**
         * Since this motor does not use feedback to control its speed, this is the
         * value that it uses to estimate the required voltage and thus the duty cycle.
         * 
         * Currently, this code assumes that the speed controller interpolates the speed linearly
         * from minimum to maximum speed. The maximum speed is assumed to be the kv constant
         * multiplied by the nominal voltage.
         * 
         * This will likely be changed after testing.
         * 
         * This is motivated by the fact that a motor controller with only 10 volts
         * can at most provide a bdlc motor 10 volts. Given the kv value, the maximum
         * theoretical speed would be that.
         */
		void setTargetSpeed(const RPM& speed) override;
        
        /**
         * This returns the desired speed, not the actual speed.
         */
		RPM getTargetSpeed() const override;

        /**
         * All requests will be clamped to this bound. The default is the maximum
         * theoretical speed which is the motor kv (1450) multiplied by the nominal
         * controller input voltage.
         */
		void setMaxSpeed(const RPM& maxSpeed);

        /**
         * Get the maximum speed which all setSpeed() requests are clamped to
         */
		RPM getMaxSpeed() const;

        /**
         * All requests will be clamped to this bound. The default for unidirectional is 0 rpm.
         * The default for bidirectional is the negative of the maximum theoretical speed.
         */
		void setMinSpeed(const RPM& minSpeed);

        /**
         * Get the minimum speed which all setSpeed requests are clamped to
         */
		RPM getMinSpeed() const;
        /**
         * This needs to have a delay of around half a second. It will be up to the caller
         * to figure out how to insure this.
         */
        void initialize() override;
        void update() override;
    private:
        RPM m_speed{0};
        RPM m_minSpeed{0};
        tap::Drivers& m_drivers;
        tap::gpio::Pwm::Pin m_pwmPin;
        const Volts mk_controllerInputVoltage;
        const RPM mk_maxTheoreticalSpeed;
        RPM m_maxSpeed;
        int8_t m_inversionMultiplier;
        // This was the Repeat Robotics provided value for the ratio between the rpm and the voltage associated with i
        //kv value is ration of rpm per voltage applied to a brushless dc motor
        static constexpr RPMPerVolt mk_kv{1450.0};
        //The voltage of the controller should not be exceeded by its output

        Vortex80AEsc m_vortex;

        /*!
            PWM should be between 0 and 1
            The motor is assumed to be in a bidirectional setup
            Therefore the if the pwm is 0.5 the motor should be still.
        */
        void setPWM(float dutyCycle);
   };
}
#endif 