#ifndef FANG_ROBOTICS_MCB_GEARED_REPEAT_ULTRA_MK2_HPP
#define FANG_ROBOTICS_MCB_GEARED_REPEAT_ULTRA_MK2_HPP
#include "unitaliases.hpp"
#include "directionality.hpp"
#include "repeatultramk2.hpp"

#include "ispeedmotor.h"
#include "tap/drivers.hpp"

namespace motors
{
    /**
    *RPM is positive according to the right hand rule when the motor is the shaft pointing up. This is the the gearbox detached!!!
    *The gear ratio is motor turns : shaft turns, so a 14:1 gearbox would mean that the motor shaft rotates 14 times in order for the
    *output shaft to rotate once.
    */
    class GearboxRepeatUltraMk2 : virtual public rail::ISpeedMotor<RPM>
    {
    public:
        GearboxRepeatUltraMk2(tap::Drivers& drivers,
                      const Volts& controllerInputVoltage,
                      tap::gpio::Pwm::Pin pwmPin,
                      const Hertz& pinFrequency,
                      data::motors::Directionality directionality = data::motors::Directionality::BIDIRECTIONAL,
                      double gearRatio);

		void setSpeed(const RPM& speed) override;
		RPM getSpeed() const override;

		void setMaxSpeed(const RPM& maxSpeed) override;
		RPM getMaxSpeed() const override;
		void setMinSpeed(const RPM& minSpeed) override;
		RPM getMinSpeed() const override;
        
        double getGearRatio() const;
    private:
        RepeatUltraMk2 m_repeatUltraMk2;
        double m_gearRatio;
        RPM m_speed{0};
        tap::Drivers& m_drivers;

        void initialize();
   };
}
#endif