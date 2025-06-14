#ifndef FANG_ROBOTICS_MCB_AIM_COMMAND_HPP
#define FANG_ROBOTICS_MCB_AIM_COMMAND_HPP
#include "configuration/motion/turret_motion_config.hpp"
#include "control/turret/turret_subsystem.hpp"
#include "control/turret/turret_input_handler.hpp"

#include "util/chrono/simple_timer.hpp"

#include "tap/control/command.hpp"

namespace control
{
    namespace turret 
    {
        class AimCommand : public tap::control::Command
        {
        public:
            AimCommand(TurretSubsystem& turret, TurretInputHandler& input, const config::motion::TurretMotionConfig& motionConfig);

            const char* getName() const override {return "Aim Command";}

            void initialize() override;
            void execute() override;
            void end(bool interrupted) override;
            bool isFinished() const override;


        private:
            void setPitch(const Microseconds& delta);
            void setYaw(const Microseconds& delta);
            turret::TurretSubsystem& m_turret;
            turret::TurretInputHandler& m_input;


            const config::motion::TurretMotionConfig mk_motionConfig;

            const Degrees mk_maxPitch;
            const Degrees mk_MinPitch;
            chrono::SimpleTimer m_executeTimer{};

            Radians m_targetPitch{0};
            Radians m_targetYaw{0};
        };
    }
}
#endif