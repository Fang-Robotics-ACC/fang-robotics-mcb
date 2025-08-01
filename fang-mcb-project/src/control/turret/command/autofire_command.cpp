#include "autofire_command.hpp"
#include "tap/algorithms/math_user_utils.hpp"

namespace fang::turret
{
    using namespace units::literals;
    AutofireCommand::AutofireCommand(ISimpleFeederSubsystem& feeder)
    :   m_feeder{feeder}
    {
        addSubsystemRequirement(&m_feeder);
    }

    void AutofireCommand::initialize()
    {
        m_feeder.feedOn();
    }

    void AutofireCommand::execute()
    {
    }

    void AutofireCommand::end(bool interrupted)
    {
        m_feeder.feedOff();
    }

    bool AutofireCommand::isFinished() const
    {
        //Only needs to switch the booster
        return false;
    }
}