#ifndef FANG_ROBOTICS_MCB_DRIVER_MOTOR_REPEAT_ULTRA_MK2_HPP
#define FANG_ROBOTICS_MCB_DRIVER_MOTOR_REPEAT_ULTRA_MK2_HPP
#include "driver/drivers.hpp"
#include "driver/motor/data/directionality.hpp"
#include "vortex_80a_esc.hpp"
#include "wrap/rail/rail_motors.hpp"
#include "wrap/units/units_alias.hpp"

#include "wrap/trap/algorithms/ramp.hpp"

#include "tap/drivers.hpp"
#include "tap/communication/gpio/pwm.hpp"
#include "wrap/trap/communication/pwm_data.hpp"

namespace fang::motor
{
    /*!
    RPM is positive according to the right hand rule when the motor is the shaft pointing up. This is the the gearbox detached!!!
    */
    class RepeatUltraMk2 : public virtual ISpeedMotor
    {
    public:
        struct Config
        {
            const Volts& controllerInputVoltage;
            trap::gpio::PwmData pwmData;
            Directionality directionality;
            bool inverted ;
        };
        RepeatUltraMk2(Drivers& drivers, const Config& config);
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
        
        void initialize() override;
        void update() override;
    private:
        const Volts kControllerInputVoltage_;
        const RPM kMaxTheoreticalSpeed_;
        RPM speed_{0};
        RPM maxSpeed_{};
        int8_t inversionMultiplier_;
        RPM minSpeed_{0};
        // This was the Repeat Robotics provided value for the ratio between the rpm and the voltage associated with i
        //kv value is ration of rpm per voltage applied to a brushless dc motor
        static constexpr RPMPerVolt kKv{1450.0};
        //The voltage of the controller should not be exceeded by its output

        Vortex80AEsc vortex_;
   };
}
#endif 