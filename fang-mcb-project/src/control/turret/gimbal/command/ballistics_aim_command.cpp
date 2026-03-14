#include "ballistics_aim_command.hpp"

#include "tap/algorithms/math_user_utils.hpp"
#include "tap/algorithms/transforms/transform.hpp"

namespace fang::turret
{
    using namespace units::literals;
    BallisticsAimCommand::BallisticsAimCommand(FieldGimbalSubsystem& gimbal, const Config& config)
    :   gimbal_{gimbal}
    {
        addSubsystemRequirement(&gimbal_);
    }

    void BallisticsAimCommand::initialize()
    {
    }

    void BallisticsAimCommand::basicTargetFound(const BasicTargetT& basicTarget)
    {
        currentTarget_ = basicTarget;
    }

    void BallisticsAimCommand::execute()
    {

        gimbal_.setTargetFieldPitch(1.0_rad);
        gimbal_.setTargetFieldYaw(1.0_rad);
    }

    BallisticsAimCommand::Vector BallisticsAimCommand::cameraToGlobal(const Vector& vector) const
    {
        
    }

    void BallisticsAimCommand::end(bool interrupted)
    {
    }

    bool BallisticsAimCommand::isFinished() const
    {
        //Default command must never finish
        return false;
    }
}