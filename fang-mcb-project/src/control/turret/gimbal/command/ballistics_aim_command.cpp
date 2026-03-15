#include "ballistics_aim_command.hpp"

#include "tap/algorithms/math_user_utils.hpp"
#include "tap/algorithms/transforms/transform.hpp"

namespace fang::turret
{
    using namespace units::literals;
    BallisticsAimCommand::BallisticsAimCommand(FieldGimbalSubsystem& gimbal, trap::communication::sensors::IImu& cameraOrientationImu, const Config& config)
    :   gimbal_{gimbal},
        cameraOrientationImu_{cameraOrientationImu}
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

        Vector globalTarget{cameraToGlobal({currentTarget_.x, currentTarget_.y, currentTarget_.z})};
        gimbal_.setTargetFieldPitch(1.0_rad);
        gimbal_.setTargetFieldYaw(1.0_rad);
    }

    BallisticsAimCommand::Vector BallisticsAimCommand::cameraToGlobal(const Vector& cameraCoordinates) const
    {
        // Currently, this only applys a rotation transform
        // Shift ofset will requrie a lot more math.
        // The robot should roughly point in the right direction still
        // reverse gimbal orientation for global
        Transform correction
        {
            Position{0,0,0},
            Orientation
            {
                0.0,
                -static_cast<double>(cameraOrientationImu_.getPitch()), 
                -static_cast<double>(cameraOrientationImu_.getYaw())
            }
        };
        return correction.apply(cameraCoordinates);
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