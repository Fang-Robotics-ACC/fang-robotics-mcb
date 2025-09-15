#include "aim_command.hpp"

#include "tap/algorithms/math_user_utils.hpp"

namespace fang::turret
{
    using namespace units::literals;
    AimCommand::AimCommand(FieldGimbalSubsystem& gimbal, ITurretInputHandler& input, const Config& config)
    :   gimbal_{gimbal},
        input_{input},
        kMaxPitchSpeed_{config.maxPitchSpeed},
        kMaxYawSpeed_{config.maxYawSpeed},
        kPitchRange_{config.pitchRange}
    {
        addSubsystemRequirement(&gimbal_);
    }

    void AimCommand::initialize()
    {
        //const Radians startingPitch{m_gimbal.getPitch()};
        //m_targetPitch = startingPitch;
        //m_gimbal.setPitch(startingPitch);
    }

    void AimCommand::execute()
    {
        const Seconds delta{executeTimer_.getDurationAndReset()};
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
        const double kPitchScalar{input_.getPitch()};
        const RPM kSpeed{kPitchScalar * kMaxPitchSpeed_};
        const Radians kAngularDisplacement{kSpeed * delta};

        const Radians kClampedDisplacement
        {
            tap::algorithms::limitVal<Radians>
            (
                kAngularDisplacement + targetPitch_,
                kPitchRange_.min,
                kPitchRange_.max
            )
        };
        targetPitch_ = kClampedDisplacement;

        gimbal_.setTargetFieldPitch(targetPitch_);
    }

    void AimCommand::setYaw(const Microseconds& delta)
    {
        const double kYawScaler{input_.getYaw()};
        const RPM kSpeed{kYawScaler * kMaxYawSpeed_};
        const Radians kAngularDisplacement{kSpeed * delta};

        targetYaw_ += kAngularDisplacement;

        gimbal_.setTargetFieldYaw(targetYaw_);
    }
}