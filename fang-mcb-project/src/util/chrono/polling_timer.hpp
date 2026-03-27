#pragma once
#include "wrap/units/units_alias.hpp"
#include "simple_timer.hpp"

namespace fang::chrono
{
/**
 * Can time stuff up to 71 days within microsecond precision
 */
class PollingTimer
{
public:
    /**
     * Automatically sets current moment to that of its creation :)
     * Sounds a bit mystical imo
     */
    PollingTimer();

    /**
     * The duration for the timer to wait.
     * 
     * The default duration is zero. Hopefully, this won't crash anything.
     */
    void setDuration(Microseconds duration);

    /**
     * Has the timer to begin timing now
     */
    void start();

    /**
     * true if the timer has elapsed
     * >= comparison
     */
    bool isFinished() const;

    /**
     * This will provide a negative value if it has not finished
     * 
     * This will allow you to compensate.
     */
    Microseconds getTimePastAlarm() const;

    /**
     * This will provide a negative value if it has finished
     * 
     * This will allow you to compensate.
     */
    Microseconds getTimeLeft() const;

    /**
     * Resets the count
     */
    void reset();

private:
    SimpleTimer simpleTimer_{};
    Microseconds timingDuration_{};
};
}