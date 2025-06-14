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
            m_turret.autoFireOff();
        }

        bool AutofireCommand::isFinished() const
        {
            //It will be removed by the command mapping
            return false;
        }
    }
}