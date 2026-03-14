#pragma once

#include "control/turret/gimbal/field_gimbal_subsystem.hpp"
#include "communication/cool_protocol/ibasic_target_listener.hpp"
#include "util/math/arithmetic/range.hpp"
#include "tap/algorithms/transforms/vector.hpp"

#include "wrap/rail/turret/igimbal_input.hpp"

#include "tap/control/command.hpp"

namespace fang::turret 
{
    /**
     * Unlike aim command, it takes the raw position instead of velocity.
     * Used for autonomous testing and as a precursor to general auto-aim commands
     */
    class BallisticsAimCommand : public tap::control::Command, public communication::IBasicTargetListener
    {
    public:
        struct Config
        {
            math::Range<Radians> pitchRange;
        };
        BallisticsAimCommand(FieldGimbalSubsystem& gimbal, const Config& config);
        void basicTargetFound(const BasicTargetT& basicTarget) override;

        const char* getName() const override {return "Ballistic Aim";}
        void initialize() override;
        void execute() override;
        void end(bool interrupted) override;
        bool isFinished() const override;

    private:
        using Vector = tap::algorithms::transforms::Vector;
        Vector cameraToGlobal(const Vector& vector) const;
        FieldGimbalSubsystem& gimbal_;
        BasicTargetT currentTarget_{};
    };
}