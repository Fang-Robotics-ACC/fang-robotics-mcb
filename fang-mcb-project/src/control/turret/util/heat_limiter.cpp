#include "heat_limiter.hpp"
namespace control::turret
{
    HeatLimiter::HeatLimiter(Referee& referee, const Config& config)
    :   m_referee{referee},
        m_criticalHeatLimit{config.criticalHeatLimit},
        m_turretId{config.turretId}
    {
    }

}