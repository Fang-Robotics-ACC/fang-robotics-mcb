#include "turret_subsystem.hpp"
namespace control
{
    namespace turret
    {
        TurretSubsystem::TurretSubsystem(Drivers& drivers, const Config& config)
        :   m_ammoBooster{drivers, config.ammoBoosterConfig},
            m_feeder{drivers, config.feederConfig},
            m_gimbal{drivers, config.gimbalConfig}
        {
        }
    }
}