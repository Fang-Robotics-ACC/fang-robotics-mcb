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
        pitchSystem_->setTargetFieldPitch(pitch);
    }

    void FieldGimbal::setTargetFieldYaw(const Radians& yaw)
    {
        yawSystem_->setTargetFieldYaw(yaw);
    }
}