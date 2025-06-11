#ifndef FANG_ROBOTICS_MCB_AIM_COMMAND_HPP
#define FANG_ROBOTICS_MCB_AIM_COMMAND_HPP
#include "turret/turret_subsystem.hpp"
#include "turret/turret_input_handler.hpp"

#include "tap/control/command.hpp"

namespace control
{
    namespace turret 
    {
        class AimCommand : public tap::control::Command
        {
        public:
            AimCommand(TurretSubsystem& turret, TurretInputHandler& input);

            const char* getName() const override {return "Aim Command";}

            void initialize() override;
            void execute() override;
            void end(bool interrupted) override;
            bool isFinished() const override;


        private:
            void setPitch();
            turret::TurretSubsystem& m_turret;
            turret::TurretInputHandler& m_input;


        };
    }
}
#endif