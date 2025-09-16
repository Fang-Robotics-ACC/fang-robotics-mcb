#pragma once

#include "control/turret/gimbal/field_gimbal_subsystem.hpp"
#include "util/math/arithmetic/range.hpp"

#include "wrap/rail/turret/iturret_input_handler.hpp"

#include "tap/control/command.hpp"

namespace fang::turret 
{
    /**
     * Unlike aim command, it takes the raw position instead of velocity.
     * Used for autonomous testing and as a precursor to general auto-aim commands
     */
    class PositionalAimCommand : public tap::control::Command
    {
    public:
        struct Config
        {
            Radians pitchScale;
            Radians yawScale;
            math::Range<Radians> pitchRange;
        };
        PositionalAimCommand(FieldGimbalSubsystem& gimbal, ITurretInputHandler& input, const Config& config);

        const char* getName() const override {return "Aim Command";}
        void initialize() override;
        void execute() override;
        void end(bool interrupted) override;
        bool isFinished() const override;

    private:
        void setPitch(const Microseconds& delta);
        void setYaw(const Microseconds& delta);
        FieldGimbalSubsystem& gimbal_;
        ITurretInputHandler& input_;

        const Radians kPitchScale_;
        const Radians kYawScale_;
        const math::Range<Radians> kPitchRange_;

        Radians targetPitch_{0};
        Radians targetYaw_{0};
    };
}