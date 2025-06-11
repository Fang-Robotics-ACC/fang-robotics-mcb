#include "control/turret/command/aim_command.hpp"

namespace control
{
    namespace turret
    {
        using namespace units::literals;
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
            //Default command must never finish
            return false;
        }

        void AimCommand::setPitch()
        {
            const double k_pitchScaler{m_input.getPitch()};
            m_turret.setPitch(k_pitchScaler * 10_deg);
        }
    }
}