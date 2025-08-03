#ifndef FANG_ROBOTICS_MCB_AIM_COMMAND_HPP
#define FANG_ROBOTICS_MCB_AIM_COMMAND_HPP
#include "control/turret/gimbal_subsystem.hpp"
#include "control/turret/turret_input_handler.hpp"

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

        };
        AimCommand(GimbalSubsystem& gimbal, TurretInputHandler& input, const Config& config);

        const char* getName() const override {return "Aim Command";}

        void initialize() override;
        void execute() override;
        void end(bool interrupted) override;
        bool isFinished() const override;


    private:
        void setPitch(const Microseconds& delta);
        void setYaw(const Microseconds& delta);
        GimbalSubsystem& m_gimbal;
        TurretInputHandler& m_input;


        const Config mk_config;

        const Degrees mk_maxPitch;
        const Degrees mk_MinPitch;
        chrono::SimpleTimer m_executeTimer{};

        Radians m_targetPitch{0};
        Radians m_targetYaw{0};
    };
}
#endif