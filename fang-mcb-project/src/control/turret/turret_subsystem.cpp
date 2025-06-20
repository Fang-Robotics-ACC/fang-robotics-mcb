#include "turret_subsystem.hpp"
#include "util/rotatevector2d.hpp"

namespace control
{
    namespace turret
    {
        TurretSubsystem::TurretSubsystem(Drivers& drivers, Imu& imu, const Config& config)
        :   Subsystem{&drivers},
            mk_homeYawOffset{config.homeYawOffset},
            m_gimbal{drivers, config.gimbalConfig},
            m_chassisImu{imu}
        {
        }

        void TurretSubsystem::initialize()
        {
            m_gimbal.initialize();
        }

        void TurretSubsystem::refresh()
        {
            syncFieldYaw();
            m_gimbal.update();
        }

        math::AbstractVector2D TurretSubsystem::getTargetFieldDirection() const
        {
            return util::math::rotateVector2D(mk_forward, m_targetFieldYaw);
        }

        void TurretSubsystem::setFieldYaw(const Radians& yaw)
        {
            m_targetFieldYaw = yaw;
        }

        void TurretSubsystem::addFieldYaw(const Radians& angle)
        {
            m_targetFieldYaw += angle;
        }

        Radians TurretSubsystem::getTargetFieldYaw() const
        {
            return m_targetFieldYaw;
        }

        void TurretSubsystem::setPitch(const Radians& pitch)
        {
            m_gimbal.setPitch(pitch);
        }

        Radians TurretSubsystem::getPitch() const
        {
            return m_gimbal.getPitch();
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

        void TurretSubsystem::syncFieldYaw()
        {
            //Start with the chassis field yaw, if you subtract the target field yaw
            //that leaves the difference, which the gimbal must do
            const Radians robotwiseYaw{getChassisYaw() - m_targetFieldYaw};
            setRawTurretRobotwiseYaw(robotwiseYaw);
        }

        Radians TurretSubsystem::getChassisYaw() const
        {
            return m_chassisImu.getYaw();
        }

        void TurretSubsystem::setRawTurretRobotwiseYaw(const Radians& yaw)
        {
            //If on startup, the turret is 45 degrees clockwise
            //Then the offset would be 45
            //Thus, if the turret is told zero degrees, then
            //the gimbal system must be tld 45 degrees counterclockwise
            m_gimbal.setYaw(yaw - mk_homeYawOffset);
        }
    }
}
