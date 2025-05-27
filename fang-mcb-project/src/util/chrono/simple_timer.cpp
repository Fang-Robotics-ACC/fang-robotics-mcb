#include "simple_timer.hpp"
#include "modm/architecture/interface/clock.hpp"
namespace chrono
{
    SimpleTimer::SimpleTimer()
    {
        reset();
    }

    void SimpleTimer::reset()
    {
        m_epoch = m_clock.now();
    }

    Microseconds SimpleTimer::getDuration() const
    {
        const RawDuration rawDuration{m_clock.now() - m_epoch};
        return Microseconds{rawDuration};
    }

    Microseconds SimpleTimer::getDurationAndReset()
    {
        //Store now so that the exact slice can be set as the new epoch
        //as time will pas when the duration is being calculated
        //and if now() was called again it could be different
        const TimePoint now{m_clock.now()};
        const RawDuration rawDuration{now - m_epoch};
        m_epoch = now;
        return Microseconds{rawDuration};
    }
}