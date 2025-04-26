#ifndef MK2_MOTORS_HPP_ASFEFKLSJKDFJSAEFE
#define MK2_MOTORS_HPP_ASFEFKLSJKDFJSAEFE
#include "idcmotor.h"
#include "iwattbudgeter.h"
#include "units.h"

#include "unitaliases.hpp"

namespace motors
{
    class RepeatUltraMk2 : virtual public rail::ISpeedMotor<MetersPerSecond, Watts>, virtual public rail::IWattBudgeter<Watts>
    {
    public:
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
   };
}
#endif 