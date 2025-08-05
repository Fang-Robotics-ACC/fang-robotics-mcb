#ifndef FANG_ROBOTICS_MCB_AIM_COMMAND_HPP
#define FANG_ROBOTICS_MCB_AIM_COMMAND_HPP
#include "control/turret/gimbal_subsystem.hpp"
#include "control/turret/gimbal/field_gimbal_subsystem.hpp"
#include "control/turret/turret_input_handler.hpp"
#include "util/math/arithmetic/range.hpp"
#include "util/chrono/simple_timer.hpp"

#include "tap/control/command.hpp"

namespace fang::turret 
{
    class AimCommand : public tap::control::Command
    {
    public:
        struct Config
        {
            RPM maxPitchSpeed;
            RPM maxYawSpeed;
            math::Range<Radians> pitchRange;
        };
        AimCommand(FieldGimbalSubsystem& gimbal, TurretInputHandler& input, const Config& config);

        const char* getName() const override {return "Aim Command";}
        void initialize() override;
        void execute() override;
        void end(bool interrupted) override;
        bool isFinished() const override;

    private:
        void setPitch(const Microseconds& delta);
        void setYaw(const Microseconds& delta);
        FieldGimbalSubsystem& gimbal_;
        TurretInputHandler& input_;

        const RPM kMaxPitchSpeed_;
        const RPM kMaxYawSpeed_;
        const math::Range<Radians> kPitchRange_;
        chrono::SimpleTimer executeTimer_{};

        Radians targetPitch_{0};
        Radians targetYaw_{0};
    };
}
#endif