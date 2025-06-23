#ifndef FANG_ROBOTICS_MCB_UNJAM_COMMAND_HPP
#define FANG_ROBOTICS_MCB_UNJAM_COMMAND_HPP
#include "control/turret/feeder_subsystem.hpp"

#include "util/chrono/simple_timer.hpp"

#include "tap/control/command.hpp"

namespace control
{
    namespace turret 
    {
        class UnjamCommand: public tap::control::Command
        {
        public:
            UnjamCommand(FeederSubsystem& feeder);

            const char* getName() const override {return "Unjam";}

            void initialize() override;
            void execute() override;
            void end(bool interrupted) override;
            bool isFinished() const override;


        private:
            FeederSubsystem& m_feeder;
        };
    }
}
#endif