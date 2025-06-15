#ifndef FANG_ROBOTICS_MCB_DEACTIVATE_BOOSTER_COMMAND_HPP
#define FANG_ROBOTICS_MCB_DEACTIVATE_BOOSTER_COMMAND_HPP
#include "control/turret/turret_subsystem.hpp"

#include "util/chrono/simple_timer.hpp"

#include "tap/control/command.hpp"

namespace control
{
    namespace turret 
    {
        class DeactivateBoosterCommand: public tap::control::Command
        {
        public:
            DeactivateBoosterCommand(TurretSubsystem& turret);

            const char* getName() const override {return "Deactivate Booster";}

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