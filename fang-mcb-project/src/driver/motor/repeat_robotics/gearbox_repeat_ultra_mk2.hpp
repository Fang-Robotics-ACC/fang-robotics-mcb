#ifndef FANG_ROBOTICS_MCB_DRIVER_MOTOR_GEARBOX_REPEAT_ULTRA_MK2_HPP
#define FANG_ROBOTICS_MCB_DRIVER_MOTOR_GEARBOX_REPEAT_ULTRA_MK2_HPP
#include "repeat_ultra_mk2.hpp"
#include "driver/motor/data/directionality.hpp"
#include "wrap/trap/communication/pwm_data.hpp"
#include "wrap/units/units_alias.hpp"

#include "driver/drivers.hpp"
#include "tap/util_macros.hpp"

namespace fang::motor
{
    /**
    *RPM is positive according to the right hand rule when the motor is the shaft pointing up. This is the the gearbox detached!!!
    *The gear ratio is motor turns : shaft turns, so a 14:1 gearbox would mean that the motor shaft rotates 14 times in order for the
    *output shaft to rotate once.
    */
    class GearboxRepeatUltraMk2 : public RepeatUltraMk2
    {
    public:
        /**
         * DEPRECATED, will be removed when the chassis code is refactored
         * These properties are the most common in being duplicate
         * across multiple instances. For your convenience, a struct
         * bundle has been provided.
         */
        struct UnifiedProperties
        {
            const Volts controllerInputVoltage;
            motor::Directionality directionality;
            double gearRatio;
        };

        struct Config
        {
            const Volts& controllerInputVoltage;
            trap::gpio::PwmData pwmData;
            motor::Directionality directionality;
            bool inverted;
            double gearRatio;
        };

        GearboxRepeatUltraMk2(Drivers& drivers, const Config& config);

        GearboxRepeatUltraMk2(tap::Drivers& drivers, const UnifiedProperties& unifiedProperties, const trap::gpio::PwmData& pwmData, bool inverted);

        GearboxRepeatUltraMk2(tap::Drivers& drivers,
                      const Volts& controllerInputVoltage,
                      tap::gpio::Pwm::Pin pwmPin,
                      const Hertz& pinFrequency,
                      motor::Directionality directionality,
                      bool inverted,
                      double gearRatio);

        mockable ~GearboxRepeatUltraMk2() = default;

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
         * All requests will be clamped to this bound. The default is the maximum
         * theoretical speed which is the motor kv (1450) multiplied by the nominal
         * controller input voltage.
         */
		mockable void setMaxSpeed(const RPM& maxSpeed);
        /**
         * Get the maximum speed which all setTargetSpeed() requests are clamped to
         */
		mockable RPM getMaxSpeed() const;

        /**
         * All requests will be clamped to this bound. The default for unidirectional is 0 rpm.
         * The default for bidirectional is the negative of the maximum theoretical speed.
         */
		mockable void setMinSpeed(const RPM& minSpeed);

        /**
         * Get the minimum speed which all setTargetSpeed requests are clamped to
         */
		mockable RPM getMinSpeed() const;
        
        /**
         * Returns the gear ratio: the amount of turns a motor makes per shaft rotation.
         */
        mockable double getGearRatio() const;
    private:
        const double kGearRatio_;

        RPM motorToShaftSpeed(const RPM& motorSpeed) const;
        RPM shaftToMotorSpeed(const RPM& shaftSpeed) const;
   };
}
#endif