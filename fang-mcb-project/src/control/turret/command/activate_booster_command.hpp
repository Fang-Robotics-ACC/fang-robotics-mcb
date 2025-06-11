#ifndef FANG_ROBOTICS_MCB_ACTIVATE_BOOSTER_COMMAND_HPP
#define FANG_ROBOTICS_MCB_ACTIVATE_BOOSTER_COMMAND_HPP
#include "control/turret/turret_subsystem.hpp"

#include "util/chrono/simple_timer.hpp"

#include "tap/control/command.hpp"

namespace control
{
    namespace turret 
    {
        class ActivateBoosterCommand: public tap::control::Command
        {
        public:
            ActivateBoosterCommand(TurretSubsystem& turret);

            const char* getName() const override {return "Activate Booster";}

            void initialize() override;
            void execute() override;
            void end(bool interrupted) override;
            bool isFinished() const override;


        private:
            turret::TurretSubsystem& m_turret;
        };
    }
}
#endif