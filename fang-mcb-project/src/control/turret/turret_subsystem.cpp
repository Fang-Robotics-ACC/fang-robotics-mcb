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

        void TurretSubsystem::flywheelsOn()
        {
            m_ammoBooster.flywheelsOn();
        }

        void TurretSubsystem::flywheelsOff()
        {
            m_ammoBooster.flywheelsOff();
        }
    }
}