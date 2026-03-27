#pragma once
#include "wrap/units/units_alias.hpp"
#include "simple_timer.hpp"

namespace fang::chrono
{
/**
 * This is designed to be able to compare between elapsed time in polling loops.
 * So you can have an event timed around a delay without having to stop execution
 * 
 * such as 
 * if (pollingTimer.isFinished)
 * {
 *     doThis();
 *     compensateDuration(pollingTimer.getTimePastAlarmAndReset());
 *     pollingTimer.restart();
 * }
 * 
 * Can time stuff up to 71 days within microsecond precision or 47 minutes double check modm
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
    void restart();

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
     * This is a special call that will allow you to precisely reset
     * the timer AND get the time past alarm without uncounted delay
     * it usees the unique implementation of SimplerTimer's getDurationAndReset
     */
    Microseconds getTimePastAlarmAndReset();

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