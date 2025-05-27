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
}