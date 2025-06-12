#include "activate_booster_command.hpp"
#include "tap/algorithms/math_user_utils.hpp"

namespace control
{
    namespace turret
    {
        using namespace units::literals;
        ActivateBoosterCommand::ActivateBoosterCommand(TurretSubsystem& turret)
        :   m_turret{turret}
        {
            addSubsystemRequirement(&m_turret);
        }

        void ActivateBoosterCommand::initialize()
        {
            m_turret.boosterOn();
        }

        void ActivateBoosterCommand::execute()
        {
        }

        void ActivateBoosterCommand::end(bool interrupted)
        {
            m_turret.boosterOff();
        }

        bool ActivateBoosterCommand::isFinished() const
        {
            //It will be removed by the command mapping
            return false;
        }
    }
}