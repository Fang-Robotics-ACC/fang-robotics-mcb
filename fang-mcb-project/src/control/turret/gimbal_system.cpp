#include "control/turret/gimbal_system.hpp"
namespace control
{
    namespace turret
    {
        GimbalSystem::GimbalSystem(Drivers& drivers, const Config& config)
        :   m_minPitch{config.minPitch}, m_maxPitch{config.maxPitch},
            m_pitchMotor{drivers, config.pitchMotorConfig},
            m_yawMotor{drivers, config.yawMotorConfig}
        {
        }

        void GimbalSystem::setPitch(const Radians& pitch)
        {
            m_pitchMotor.setTargetPosition(pitch);
        }

        void GimbalSystem::addPitch(const Radians& angle)
        {
            setPitch(getPitch() + angle);
        }

        Radians GimbalSystem::getPitch() const
        {
            return m_pitchMotor.getPosition();
        }

        void GimbalSystem::setYaw(const Radians& yaw)
        {
            m_yawMotor.setTargetPosition(yaw);
        }

        void GimbalSystem::addYaw(const Radians& angle)
        {
            setYaw(getYaw() + angle);
        }

        Radians GimbalSystem::getYaw() const
        {
            return m_yawMotor.getPosition();
        }

        void GimbalSystem::update()
        {
            m_pitchMotor.update();
            m_yawMotor.update();
        }
    }
}