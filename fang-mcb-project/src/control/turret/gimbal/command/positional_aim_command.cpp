#include "positional_aim_command.hpp"

#include "tap/algorithms/math_user_utils.hpp"

namespace fang::turret
{
    using namespace units::literals;
    PositionalAimCommand::PositionalAimCommand(FieldGimbalSubsystem& gimbal, ITurretInputHandler& input, const Config& config)
    :   gimbal_{gimbal},
        input_{input},
        kPitchScale_{config.pitchScale},
        kYawScale_{config.yawScale},
        kPitchRange_{config.pitchRange}
    {
        addSubsystemRequirement(&gimbal_);
    }

    void PositionalAimCommand::initialize()
    {
        //const Radians startingPitch{m_gimbal.getPitch()};
        //m_targetPitch = startingPitch;
        //m_gimbal.setPitch(startingPitch);
    }

    void PositionalAimCommand::execute()
    {
        gimbal_.setTargetFieldPitch(input_.getPitch() * kPitchScale_);
        gimbal_.setTargetFieldYaw(input_.getYaw() * kYawScale_);
    }

    void PositionalAimCommand::end(bool interrupted)
    {
    }

    bool PositionalAimCommand::isFinished() const
    {
        //Default command must never finish
        return false;
    }
}