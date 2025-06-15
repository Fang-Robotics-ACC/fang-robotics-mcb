#include "stop_autofire_command.hpp"
#include "tap/algorithms/math_user_utils.hpp"

namespace control
{
    namespace turret
    {
        using namespace units::literals;
        StopAutofireCommand::StopAutofireCommand(TurretSubsystem& turret)
        :   m_turret{turret}
        {
            addSubsystemRequirement(&m_turret);
        }

        void StopAutofireCommand::initialize()
        {
            m_turret.autoFireOff();
        }

        void StopAutofireCommand::execute()
        {
        }

        void StopAutofireCommand::end(bool interrupted)
        {
        }

        bool StopAutofireCommand::isFinished() const
        {
            //Instant command
            return true;
        }
    }
}