#pragma once

#include "control/turret/gimbal/field_gimbal_subsystem.hpp"
#include "driver/drivers.hpp"
#include "wrap/rail/turret/ifield_yaw_system.hpp"
#include "wrap/rail/turret/ifield_pitch_system.hpp"

#include <memory>

namespace fang::turret
{
    /**
     * Takes a field and pitch system
     */
    class FieldGimbal: public FieldGimbalSubsystem
    {
        FieldGimbal
        (
            Drivers& drivers,
            std::unique_ptr<IFieldPitchSystem> pitchSystem,
            std::unique_ptr<IFieldYawSystem> yawSystem
        );

        void initialize() override;
        void update() override;
        void setTargetFieldPitch(const Radians& pitch) override;
        void setTargetFieldYaw(const Radians& yaw) override;

    private:
        std::unique_ptr<IFieldPitchSystem> pitchSystem_;
        std::unique_ptr<IFieldYawSystem> yawSystem_;
    };
}