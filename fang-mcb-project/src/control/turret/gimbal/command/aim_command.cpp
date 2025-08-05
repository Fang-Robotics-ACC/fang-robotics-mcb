#include "aim_command.hpp"

#include "tap/algorithms/math_user_utils.hpp"

namespace fang::turret
{
    using namespace units::literals;
    AimCommand::AimCommand(FieldGimbalSubsystem& gimbal, TurretInputHandler& input, const Config& config)
    :   m_gimbal{gimbal},
        m_input{input},
        kMaxPitchSpeed_{config.maxPitchSpeed},
        kMaxYawSpeed_{config.maxYawSpeed},
        kPitchRange_{config.pitchRange}
    {
        addSubsystemRequirement(&m_gimbal);
    }

    void AimCommand::initialize()
    {
        //const Radians startingPitch{m_gimbal.getPitch()};
        //m_targetPitch = startingPitch;
        //m_gimbal.setPitch(startingPitch);
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
        const RPM k_speed{k_pitchScaler * kMaxPitchSpeed_};
        const Radians k_angularDisplacement{k_speed * delta};

        const Radians kClampedDisplacement
        {
            tap::algorithms::limitVal<Radians>
            (
                k_angularDisplacement + m_targetPitch,
                kPitchRange_.min,
                kPitchRange_.max
            )
        };
        m_targetPitch = kClampedDisplacement;

        m_gimbal.setTargetFieldPitch(m_targetPitch);
    }

    void AimCommand::setYaw(const Microseconds& delta)
    {
        const double k_yawScaler{m_input.getYaw()};
        const RPM k_speed{k_yawScaler * kMaxYawSpeed_};
        const Radians k_angularDisplacement{k_speed * delta};

        targetYaw_ += k_angularDisplacement;

        m_gimbal.setTargetFieldYaw(targetYaw_);
    }
}