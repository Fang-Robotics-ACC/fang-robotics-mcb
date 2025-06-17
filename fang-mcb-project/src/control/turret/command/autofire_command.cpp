#include "autofire_command.hpp"
#include "tap/algorithms/math_user_utils.hpp"

namespace control
{
    namespace turret
    {
        using namespace units::literals;
        AutofireCommand::AutofireCommand(TurretSubsystem& turret)
        :   m_turret{turret}
        {
            addSubsystemRequirement(&m_turret);
        }

        void AutofireCommand::initialize()
        {
            m_turret.autoFireOn();
        }

        void AutofireCommand::execute()
        {
        }

        void AutofireCommand::end(bool interrupted)
        {
        }

        bool AutofireCommand::isFinished() const
        {
            //Only needs to switch the booster
            return true;
        }
    }
}