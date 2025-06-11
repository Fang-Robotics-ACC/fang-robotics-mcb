#include "control/turret/command/aim_command.hpp"

namespace control
{
    namespace turret
    {
        AimCommand::AimCommand(TurretSubsystem& turret, TurretInputHandler& input)
        :   m_turret{turret},
            m_input{input}
        {
            addSubsystemRequirement(&m_turret);
        }

        void AimCommand::initialize()
        {

        }

        void AimCommand::execute()
        {

        }

        void AimCommand::end(bool interrupted)
        {

        }

        bool AimCommand::isFinished() const
        {

        }

    }
}