#ifndef FANG_ROBOTICS_MCB_UNJAM_COMMAND_HPP
#define FANG_ROBOTICS_MCB_UNJAM_COMMAND_HPP
#include "wrap/rail/rail_turret_aliases.hpp"

#include "util/chrono/simple_timer.hpp"

#include "tap/control/command.hpp"

namespace control
{
    namespace turret 
    {
        class UnjamCommand: public tap::control::Command
        {
        public:
            UnjamCommand(ISimpleFeederSubsystemControl& feeder);

            const char* getName() const override {return "Unjam";}

            void initialize() override;
            void execute() override;
            void end(bool interrupted) override;
            bool isFinished() const override;


        private:
           ISimpleFeederSubsystemControl& m_feeder;
        };
    }
}
#endif