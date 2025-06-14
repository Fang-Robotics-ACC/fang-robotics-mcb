#include "turret_subsystem.hpp"

namespace control
{
    namespace turret
    {
        TurretSubsystem::TurretSubsystem(Drivers& drivers, const Config& config)
        :   Subsystem{&drivers},
            m_gimbal{drivers, config.gimbalConfig},
            m_booster{drivers, config.ammoConfig},
            m_chassisImu{drivers.bmi088}
        {
        }

        void TurretSubsystem::initialize()
        {
            m_gimbal.initialize();
            m_booster.initialize();
        }

        void TurretSubsystem::refresh()
        {
            syncFieldYaw();
            m_gimbal.update();
            m_booster.update();
        }

        void TurretSubsystem::setFieldYaw(const Radians& yaw)
        {
            m_targetFieldYaw();
        }

        void TurretSubsystem::addFieldYaw(const Radians& angle)
        {
            m_targetFieldYaw += angle;
        }

        void TurretSubsystem::setPitch(const Radians& pitch)
        {
            m_gimbal.setPitch(pitch);
        }

        void TurretSubsystem::addPitch(const Radians& angle)
        {
            m_gimbal.addPitch(angle);
        }

        Radians TurretSubsystem::getMaxPitch() const
        {
            return m_gimbal.getMaxPitch();
        }
        Radians TurretSubsystem::getMinPitch() const
        {
            return m_gimbal.getMinPitch();
        }

        void TurretSubsystem::boosterOn()
        {
            m_booster.autoFireOn();
        }
        void TurretSubsystem::boosterOff()
        {
            m_booster.autoFireOff();
        }

        void TurretSubsystem::syncFieldYaw()
        {
            const Radians gimbal_yaw{m_targetFieldYaw - getChassisYaw()};
            m_gimbal.setYaw(gimbal_yaw);
        }

        Radians TurretSubsystem::getChassisYaw() const
        {
            m_chassisImu.getYaw();
        }
    }
}