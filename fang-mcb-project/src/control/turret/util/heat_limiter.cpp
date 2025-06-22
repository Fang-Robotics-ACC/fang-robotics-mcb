#include "heat_limiter.hpp"
namespace control::turret
{
    HeatLimiter::HeatLimiter(Referee& referee, const Config& config)
    :   m_referee{referee},
        m_criticalHeatLimit{config.criticalHeatLimit},
        m_turretId{config.turretId}
    {
    }

    HeatLimiter::HeatType HeatLimiter::getTurretHeat() const
    {
        const Referee::Rx::TurretData turretData{m_referee.getRobotData().turret};
        switch(m_turretId)
        {
            case TurretId::TURRET_17MM_1:
                return turretData.heat17ID1;
                break;
            case TurretId::TURRET_17MM_2:
                return turretData.heat17ID2;
                break;
            case TurretId::TURRET_42MM:
                return turretData.heat42;
                break;
        }
    }

}