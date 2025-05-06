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
    class RepeatUltraMk2 : virtual public rail::ISpeedMotor<RPM>, virtual public rail::IWattBudgeter<Watts>
    {
    public:
        RepeatUltraMk2(tap::Drivers& drivers,
                      const Volts& controllerInputVoltage,
                      tap::gpio::Pwm::Pin pwmPin,
                      const Hertz& pinFrequency,
                      data::motors::Directionality directionality = data::motors::Directionality::BIDIRECTIONAL);

        /// @brief Does not limit anything yet
        /// @param wattage 
        void setWattBudget(const Watts& wattage) override;

        /// Does not limit anything yet
		Watts getWattBudget() const override;
        
        //Does not do anything
		virtual void setWattEstimateMode(bool mode) override;
		virtual bool estimateModeAllowed() const override {return mk_estimateModeAllowed;}
		virtual bool getWattOverbudgetStatus() const override;
		virtual void resetWattOverbudgetStatus() override;
        //Does not do anything
		virtual Watts getWattOverbudgetAmount() const override;

		void setSpeed(const RPM& speed) override;
		RPM getSpeed() const override;

		void setMaxSpeed(const RPM& maxSpeed) override;
		RPM getMaxSpeed() const override;
		void setMinSpeed(const RPM& minSpeed) override;
		RPM getMinSpeed() const override;
    private:
        Watts m_wattBudget{0};
        Watts m_maxWattBudget{0};
        Watts m_minWattBudget{0};
        bool  m_estimateMode{0};
        bool  m_overbudgetStatus{false};
        const bool mk_estimateModeAllowed{false};

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