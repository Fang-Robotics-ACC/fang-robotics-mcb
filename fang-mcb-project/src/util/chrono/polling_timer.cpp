#include "polling_timer.hpp"

namespace fang::chrono
{

PollingTimer::PollingTimer()
{
}

void PollingTimer::setDuration(Microseconds duration)
{
    timingDuration_ = duration;
}

void PollingTimer::start()
{
    simpleTimer_.reset();
}

bool PollingTimer::isFinished() const
{
    return simpleTimer_.getDuration() >= timingDuration_;
}

Microseconds PollingTimer::getTimePastAlarm() const
{
    return simpleTimer_.getDuration() - timingDuration_;
}

Microseconds PollingTimer::getTimeLeft() const
{
    return -getTimePastAlarm();
}
}