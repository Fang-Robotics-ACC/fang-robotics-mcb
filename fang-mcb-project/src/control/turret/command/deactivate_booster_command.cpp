#include "deactivate_booster_command.hpp"
#include "tap/algorithms/math_user_utils.hpp"

namespace control
{
    namespace turret
    {
        using namespace units::literals;
        DeactivateBoosterCommand::DeactivateBoosterCommand(TurretSubsystem& turret)
        :   m_turret{turret}
        {
            addSubsystemRequirement(&m_turret);
        }

        void DeactivateBoosterCommand::initialize()
        {
            m_turret.boosterOff();
        }

        void DeactivateBoosterCommand::execute()
        {
        }

        void DeactivateBoosterCommand::end(bool interrupted)
        {
        }

        bool DeactivateBoosterCommand::isFinished() const
        {
            //Instant command
            return true;
        }
    }
}