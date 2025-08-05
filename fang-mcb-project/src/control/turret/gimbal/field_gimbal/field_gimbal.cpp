#include "field_gimbal.hpp"

namespace fang::turret
{
    FieldGimbal::FieldGimbal
    (
        Drivers& drivers,
        std::unique_ptr<IFieldPitchSystem> pitchSystem,
        std::unique_ptr<IFieldYawSystem> yawSystem
    ):
        FieldGimbalSubsystem{drivers},
        pitchSystem_{std::move(pitchSystem)},
        yawSystem_{std::move(yawSystem)}
    {}

    void FieldGimbal::initialize()
    {
        pitchSystem_->initialize();
        yawSystem_->initialize();
    }

    void FieldGimbal::update()
    {
        pitchSystem_->update();
        yawSystem_->update();
    }

    void FieldGimbal::setTargetFieldPitch(const Radians& pitch)
    {
        targetFieldPitch_ = pitch;
        pitchSystem_->setTargetFieldPitch(targetFieldPitch_);
    }

    void FieldGimbal::setTargetFieldYaw(const Radians& yaw)
    {
        targetFieldYaw_ = yaw;
        yawSystem_->setTargetFieldYaw(targetFieldYaw_);
    }

    Radians FieldGimbal::getTargetFieldPitch() const
    {
        return targetFieldPitch_;
    }

    Radians FieldGimbal::getTargetFieldYaw() const
    {
        return targetFieldYaw_;
    }
}