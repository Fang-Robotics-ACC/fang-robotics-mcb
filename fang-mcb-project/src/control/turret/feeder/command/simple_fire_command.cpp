#include "simple_fire_command.hpp"
#include "tap/algorithms/math_user_utils.hpp"

namespace fang::turret
{
    using namespace units::literals;
    FireCommand::FireCommand(SimpleFeederSubsystem& feeder)
    :   m_feeder{feeder}
    {
        addSubsystemRequirement(&m_feeder);
    }

    void FireCommand::initialize()
    {
        m_feeder.feedOn();
    }

    void FireCommand::execute()
    {
    }

    void FireCommand::end(bool interrupted)
    {
        m_feeder.feedOff();
    }

    bool FireCommand::isFinished() const
    {
        //Only needs to switch the booster
        return false;
    }
} 