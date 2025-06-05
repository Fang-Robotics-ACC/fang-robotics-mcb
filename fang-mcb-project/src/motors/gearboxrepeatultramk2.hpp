#ifndef FANG_ROBOTICS_MCB_GEARED_REPEAT_ULTRA_MK2_HPP
#define FANG_ROBOTICS_MCB_GEARED_REPEAT_ULTRA_MK2_HPP
#include "unitaliases.hpp"
#include "directionality.hpp"
#include "repeatultramk2.hpp"
#include "wrap/trap/communication/pwm_data.hpp"

#include "ispeedmotor.h"
#include "drivers.hpp"
#include "tap/util_macros.hpp"

namespace motors
{
    /**
    *RPM is positive according to the right hand rule when the motor is the shaft pointing up. This is the the gearbox detached!!!
    *The gear ratio is motor turns : shaft turns, so a 14:1 gearbox would mean that the motor shaft rotates 14 times in order for the
    *output shaft to rotate once.
    */
    class GearboxRepeatUltraMk2 : virtual public rail::ISpeedMotor<RPM>, public RepeatUltraMk2
    {
    public:
        /**
         * These properties are the most common in being duplicate
         * across multiple instances. For your convenience, a struct
         * bundle has been provided.
         */
        struct UnifiedProperties
        {
            const Volts controllerInputVoltage;
            data::motors::Directionality directionality;
            double gearRatio;
        };

        GearboxRepeatUltraMk2(tap::Drivers& drivers, const UnifiedProperties& unifiedProperties, const trap::gpio::PwmData& pwmData, bool inverted);

        GearboxRepeatUltraMk2(tap::Drivers& drivers,
                      const Volts& controllerInputVoltage,
                      tap::gpio::Pwm::Pin pwmPin,
                      const Hertz& pinFrequency,
                      data::motors::Directionality directionality,
                      bool inverted,
                      double gearRatio);

        mockable ~GearboxRepeatUltraMk2() = default;

        /**
         * This returns the desired speed, not the actual speed.
         */

		mockable void setMaxSpeed(const RPM& maxSpeed) override;

        /**
         * All requests will be clamped to this bound. The default is the maximum
         * theoretical speed which is the motor kv (1450) multiplied by the nominal
         * controller input voltage.
         */
		mockable RPM getSpeed() const override;

        /**
         * Get the maximum speed which all setSpeed() requests are clamped to
         */
		mockable RPM getMaxSpeed() const override;

        /**
         * All requests will be clamped to this bound. The default for unidirectional is 0 rpm.
         * The default for bidirectional is the negative of the maximum theoretical speed.
         */
		mockable void setMinSpeed(const RPM& minSpeed) override;

        /**
         * Get the minimum speed which all setSpeed requests are clamped to
         */
		mockable RPM getMinSpeed() const override;
        
        /**
         * Returns the gear ratio: the amount of turns a motor makes per shaft rotation.
         */
        mockable double getGearRatio() const;
    private:
        double m_gearRatio;
        RPM m_speed{0};

        RPM motorToShaftSpeed(const RPM& motorSpeed) const;
        RPM shaftToMotorSpeed(const RPM& shaftSpeed) const;
   };
}
#endif