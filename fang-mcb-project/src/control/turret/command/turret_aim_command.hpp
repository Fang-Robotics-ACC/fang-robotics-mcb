#ifndef FANG_ROBOTICS_MCB_TURRET_AIM_COMMAND_HPP
#define FANG_ROBOTICS_MCB_TURRET_AIM_COMMAND_HPP
#include "configuration/motion/turret_motion_config.hpp"
#include "control/turret/turret_subsystem.hpp"
#include "control/turret/turret_input_handler.hpp"

#include "util/chrono/simple_timer.hpp"

#include "tap/control/command.hpp"

#include "unitaliases.hpp"

namespace control
{
    namespace turret
    {
        /**
         * Aims the turret
         */
        class TurretAimCommand : public tap::control::Command
        {
        public:
            TurretAimCommand(TurretSubsystem& turret, TurretInputHandler& input, const config::motion::TurretConfig& motionConfig);
            const char* getName() const override;
            void initialize() override;
            void execute() override;
            void end(bool interrupted) override;
            bool isFinished() const;
        private:
            void setPitchSpeed(const Seconds& delta);
            void setYawSpeed(const Seconds& delta);

            Radians rpmToDisplacement(const RPM& speed, const Seconds& time) const;
            static constexpr char* mk_name{"Turret Aim Command"};
            TurretSubsystem& m_turret;
            TurretInputHandler& m_input;

            chrono::SimpleTimer m_executeTimer();
            const config::motion::TurretConfig& mk_motionConfig;
        };
    }
}
#endif