#include "control/turret/gimbal_system.hpp"
#include "tap/algorithms/math_user_utils.hpp"
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
            const Radians limitedPitch{tap::algorithms::limitVal<Radians>(pitch, m_minPitch, m_maxPitch)};
            m_pitchMotor.setTargetPosition(limitedPitch);
        }

        void GimbalSystem::addPitch(const Radians& angle)
        {
            setPitch(getPitch() + angle);
        }

        Radians GimbalSystem::getPitch() const
        {
            return m_pitchMotor.getPosition();
        }

        Radians GimbalSystem::getMaxPitch() const
        {
            return m_maxPitch;
        }

        Radians GimbalSystem::getMinPitch() const
        {
            return m_minPitch;
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

        void GimbalSystem::initialize()
        {
            m_pitchMotor.initialize();
            m_yawMotor.initialize();
        }
    }
}