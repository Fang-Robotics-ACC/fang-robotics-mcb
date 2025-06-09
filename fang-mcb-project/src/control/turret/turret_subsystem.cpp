#include "turret_subsystem.hpp"
namespace control
{
    namespace turret
    {
        TurretSubsystem::TurretSubsystem(Drivers& drivers, const Config& config)
        :   m_imu{drivers.bmi088},
            m_ammoBooster{drivers, config.ammoBoosterConfig},
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

        void TurretSubsystem::autoFireOn()
        {
            if(m_ammoBooster.getFlywheelStatus())
            {
                m_feeder.feedOn();
            }
        }

        void TurretSubsystem::autoFireOff()
        {
            m_feeder.feedOff();
        }

        void TurretSubsystem::setPitch(const Radians& pitch)
        {
            m_gimbal.setPitch(pitch);
        }

        void TurretSubsystem::setFieldYaw(const Radians& yaw)
        {
        }

        Radians TurretSubsystem::getChassisFieldRotation() const
        {
            return Radians{m_imu.getYaw()};
        }
    }
}