#include "control/turret/command/turret_aim_command.hpp"

namespace control
{
    namespace turret
    {
        TurretAimCommand::TurretAimCommand(TurretSubsystem& turret, TurretInputHandler& input)
        :   m_turret{turret}, m_input{input}
        {
        }
    }
}