#include "control/turret/command/turret_aim_command.hpp"

namespace control
{
    namespace turret
    {
        TurretAimCommand::TurretAimCommand(TurretSubsystem& turret, TurretInputHandler& input)
        :   m_turret{turret}, m_input{input}
        {
        }

        const char* TurretAimCommand::getName() const
        {
            return mk_name;
        }

        void TurretAimCommand::initialize()
        {
        }

        void TurretAimCommand::execute()
        {
        }

        void TurretAimCommand::end(bool interrupted)
        {
        }

        bool TurretAimCommand::isFinished() const
        {
            //This is meant to be a default command
            return false;
        }
    }
}