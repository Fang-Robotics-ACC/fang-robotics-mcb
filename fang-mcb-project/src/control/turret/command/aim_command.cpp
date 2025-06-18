#include "control/turret/command/aim_command.hpp"

#include "tap/algorithms/math_user_utils.hpp"

namespace control
{
    namespace turret
    {
        using namespace units::literals;
        AimCommand::AimCommand(GimbalSubsystem& gimbal, TurretInputHandler& input, const Config& config)
        :   m_gimbal{gimbal},
            m_input{input},
            mk_config{config},
            mk_maxPitch{m_gimbal.getMaxPitch()},
            mk_MinPitch{m_gimbal.getMinPitch()}
        {
            addSubsystemRequirement(&m_gimbal);
        }

        void AimCommand::initialize()
        {
        }

        void AimCommand::execute()
        {
            const Seconds delta{m_executeTimer.getDurationAndReset()};
            setPitch(delta);
            setYaw(delta);
        }

        void AimCommand::end(bool interrupted)
        {
        }

        bool AimCommand::isFinished() const
        {
            //Default command must never finish
            return false;
        }

        void AimCommand::setPitch(const Microseconds& delta)
        {
            const double k_pitchScaler{m_input.getPitch()};
            const RPM k_speed{k_pitchScaler * mk_config.maxPitchSpeed};
            const Radians k_angularDisplacement{k_speed * delta};

            m_targetPitch =tap::algorithms::limitVal<Radians>(k_angularDisplacement + m_targetPitch, mk_MinPitch, mk_maxPitch);

            m_gimbal.setPitch(m_targetPitch);
        }

        void AimCommand::setYaw(const Microseconds& delta)
        {
            const double k_yawScaler{m_input.getYaw()};
            const RPM k_speed{k_yawScaler * mk_config.maxYawSpeed};
            const Radians k_angularDisplacement{k_speed * delta};

            m_targetYaw += k_angularDisplacement;

            m_gimbal.setFieldYaw(m_targetYaw);
        }
    }
}