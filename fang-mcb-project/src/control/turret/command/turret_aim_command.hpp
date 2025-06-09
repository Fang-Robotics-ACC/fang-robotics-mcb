#ifndef FANG_ROBOTICS_MCB_TURRET_AIM_COMMAND_HPP
#define FANG_ROBOTICS_MCB_TURRET_AIM_COMMAND_HPP
#include "control/turret/turret_subsystem.hpp"
#include "control/turret/turret_input_handler.hpp"

#include "tap/control/command.hpp"

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
            TurretAimCommand(TurretSubsystem& turret, TurretInputHandler& input);
            const char* getName() const override;
            void initialize() override;
            void execute() override;
            void end(bool interrupted) override;
            bool isFinished() const;
        private:
            void aimPitch();
            void aimYaw();
            static constexpr char* mk_name{"Turret Aim Command"};
            TurretSubsystem& m_turret;
            TurretInputHandler& m_input;
        };
    }
}
#endif