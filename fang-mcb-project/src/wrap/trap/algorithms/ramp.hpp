#ifndef FANG_ROBOTICS_MCB_TRAP_ALGORITHMS_RAMP_HPP
#define FANG_ROBOTICS_MCB_TRAP_ALGORITHMS_RAMP_HPP
#include "util/chrono/simple_timer.hpp"

#include "tap/algorithms/ramp.hpp"
#include "tap/util_macros.hpp"
namespace trap::algorithms
{
    /**
     * Dimensional wrap for taproot ramp
     */
    template <typename ValueUnit, typename TimeUnit>
    class Ramp
    {
    public:
        /**
         * Speed should be positive
         */
        Ramp(ValueUnit initialValue, double rampSpeed)
        :   m_ramp{static_cast<float>(initialValue)},
            m_speed{rampSpeed}
        {
        }

        mockable void setTarget(ValueUnit target)
        {
            m_ramp.setTarget(static_cast<float>(target));
        }

        mockable ValueUnit getTarget() const
        {
            return ValueUnit{m_ramp.getTarget()};
        }

        /**
         * How many units per time unit the ramp moves towards the target value
         * 
         * This should be positive`
         * 
         * This is a float to allow ramp to use primitive types
         */
        mockable void setSpeed(double speed)
        {
            m_speed = speed;
        }

        mockable void update()
        {
            const TimeUnit deltaTime{static_cast<TimeUnit>(m_updateTimer.getDurationAndReset())};
            const double rawDeltaTime{static_cast<double>(deltaTime)};
            const double increment{m_speed * rawDeltaTime};

            m_ramp.update(increment);
        }

        mockable ValueUnit getValue() const
        {
            return ValueUnit{m_ramp.getValue()};
        }

        mockable bool isTargetReached() const
        {
            return m_ramp.isTargetReached();
        }

    private:
        tap::algorithms::Ramp m_ramp;
        double m_speed;
        fang::chrono::SimpleTimer m_updateTimer{};

    };
}
#endif
