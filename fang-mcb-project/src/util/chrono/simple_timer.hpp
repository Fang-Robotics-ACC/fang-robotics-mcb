#ifndef FANG_ROBOTICS_MCB_TIME_SIMPLER_TIMER_HPP
#define FANG_ROBOTICS_MCB_TIME_SIMPLER_TIMER_HPP
#include "wrap/units/units_alias.hpp"
#include "modm/architecture/interface/clock.hpp"

namespace fang::chrono
{
    /**
     * Can time stuff up to 71 days within microsecond precision
     */
    class SimpleTimer
    {
        //Microseconds
        using TimePoint = modm::chrono::micro_clock::time_point;
        using RawDuration = modm::PreciseClock::duration;
        using Clock = modm::PreciseClock;
    public:
        /**
         * Automatically sets current moment to that of its creation :)
         * Sounds a bit mystical imo
         */
        SimpleTimer();
        /**
         * Resets the count and returns the duration.
         * Slightly more accurate.
         */
        Microseconds getDurationAndReset();

        /**
         * Resets the count
         */
        void reset();

        /**
         * Returns the duration
         */
        Microseconds getDuration() const;
    private:
        Clock m_clock;
        TimePoint m_epoch;
    };
}
#endif