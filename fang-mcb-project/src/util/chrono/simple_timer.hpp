#ifndef FANG_ROBOTICS_MCB_TIME_SIMPLER_TIMER_HPP
#define FANG_ROBOTICS_MCB_TIME_SIMPLER_TIMER_HPP
#include "configuration/unitaliases.hpp"

namespace chrono
{
    /**
     * Can time stuff up to 71 days within microsecond precision
     */
    class SimpleTimer
    {
    public:
        SimpleTimer() = default;
        /**
         * Resets the count and returns the duration
         */
        Milliseconds getDurationAndReset();

        /**
         * Resets the count
         */
        void reset();

        /**
         * Returns the duration
         */
        Milliseconds getDuration() const;
    };
}
#endif