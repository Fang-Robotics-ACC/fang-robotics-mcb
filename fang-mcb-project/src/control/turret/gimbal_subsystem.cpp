#include "gimbal_subsystem.hpp"
#include "util/rotatevector2d.hpp"

namespace control
{
    namespace turret
    {
        GimbalSubsystem::GimbalSubsystem(Drivers& drivers, Imu& chassisImu, const Config& config)
        :   Subsystem{&drivers},
            mk_homeYawOffset{config.homeYawOffset},
            m_gimbal{drivers, config.gimbalConfig},
            m_chassisImu{chassisImu}
        {
        }

        void GimbalSubsystem::initialize()
        {
            m_gimbal.initialize();
        }

        void GimbalSubsystem::refresh()
        {
            syncFieldYaw();
            m_gimbal.update();
        }

        math::AbstractVector2D GimbalSubsystem::getTargetFieldDirection() const
        {
            return util::math::rotateVector2D(mk_forward, m_targetFieldYaw);
        }

        void GimbalSubsystem::setFieldYaw(const Radians& yaw)
        {
            m_targetFieldYaw = yaw;
        }

        void GimbalSubsystem::addFieldYaw(const Radians& angle)
        {
            m_targetFieldYaw += angle;
        }

        Radians GimbalSubsystem::getTargetFieldYaw() const
        {
            return m_targetFieldYaw;
        }

        void GimbalSubsystem::setPitch(const Radians& pitch)
        {
            m_gimbal.setPitch(pitch);
        }

        Radians GimbalSubsystem::getPitch() const
        {
            return m_gimbal.getPitch();
        }

        void GimbalSubsystem::addPitch(const Radians& angle)
        {
            m_gimbal.addPitch(angle);
        }

        Radians GimbalSubsystem::getMaxPitch() const
        {
            return m_gimbal.getMaxPitch();
        }
        Radians GimbalSubsystem::getMinPitch() const
        {
            return m_gimbal.getMinPitch();
        }

        void GimbalSubsystem::syncFieldYaw()
        {
            //Start with the chassis field yaw, if you subtract the target field yaw
            //that leaves the difference, which the gimbal must do
            const Radians robotwiseYaw{m_targetFieldYaw - getChassisYaw()};
            setRawTurretRobotwiseYaw(robotwiseYaw);
        }

        Radians GimbalSubsystem::getChassisYaw() const
        {
            return m_chassisImu.getYaw();
        }

        void GimbalSubsystem::setRawTurretRobotwiseYaw(const Radians& yaw)
        {
            //If on startup, the turret is 45 degrees clockwise
            //Then the offset would be 45
            //Thus, if the turret is told zero degrees, then
            //the gimbal system must be tld 45 degrees counterclockwise
            m_gimbal.setYaw(yaw - mk_homeYawOffset);
        }
    }
}
