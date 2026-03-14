#pragma once

#include "control/turret/gimbal/field_gimbal_subsystem.hpp"
#include "util/math/arithmetic/range.hpp"

#include "wrap/rail/turret/igimbal_input.hpp"

#include "tap/control/command.hpp"

namespace fang::turret 
{
    /**
     * Unlike aim command, it takes the raw position instead of velocity.
     * Used for autonomous testing and as a precursor to general auto-aim commands
     */
    class BallisticsAimCommand : public tap::control::Command
    {
    public:
        struct Config
        {
            math::Range<Radians> pitchRange;
        };
        BallisticsAimCommand(FieldGimbalSubsystem& gimbal, const Config& config);

        const char* getName() const override {return "Ballistic Aim";}
        void initialize() override;
        void execute() override;
        void end(bool interrupted) override;
        bool isFinished() const override;

    private:
        FieldGimbalSubsystem& gimbal_;
    };
}