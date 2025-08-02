#ifndef FANG_ROBOTICS_MCB_DRIVER_MOTOR_GEARBOX_REPEAT_ULTRA_MK2_HPP
#define FANG_ROBOTICS_MCB_DRIVER_MOTOR_GEARBOX_REPEAT_ULTRA_MK2_HPP

#include "vortex_80a_esc.hpp"
#include "driver/drivers.hpp"

#include "wrap/rail/motor/ispeed_motor.hpp"
#include "wrap/trap/communication/pwm_data.hpp"
#include "wrap/units/units_alias.hpp"

#include "tap/util_macros.hpp"

namespace fang::motor
{
    /**
    *RPM is positive according to the right hand rule when the motor is the shaft pointing up. This is the the gearbox detached!!!
    *The gear ratio is motor turns : shaft turns, so a 14:1 gearbox would mean that the motor shaft rotates 14 times in order for the
    *output shaft to rotate once.
    */
    class UltraMk2 : public ISpeedMotor
    {
    public:
        struct Config
        {
            const Volts& controllerInputVoltage;
            trap::gpio::PwmData pwmData;
            bool inverted;
            double gearRatio;
        };

        UltraMk2(Drivers& drivers, const Config& config);

        mockable ~UltraMk2() = default;

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
		mockable void setTargetSpeed(const RPM& speed);

        /**
         * Required to send a zero arming signal
         * The initialization needs to have an arming signal sent for
         * 1-2 seconds. It will be left up to the caller on how to 
         * ensure the delay.
         */
        void initialize() override;

        void update();

        static constexpr RPMPerVolt kKv{1450.0};
    private:
        const Volts kControllerInputVoltage_;
        const double kGearRatio_;
        const int8_t kInversionMultiplier_;
        // This was the Repeat Robotics provided value for the ratio between the rpm and the voltage associated with i
        //kv value is ration of rpm per voltage applied to a brushless dc motor
        Vortex80AEsc vortex_;

        const RPM kMaxTheoreticalSpeed_{kKv * kControllerInputVoltage_};
   };
}
#endif