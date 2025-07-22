#include "unjam_command.hpp"
#include "tap/algorithms/math_user_utils.hpp"

namespace fang::turret
{
    using namespace units::literals;
    UnjamCommand::UnjamCommand(ISimpleFeederSubsystemControl& feeder)
    :   m_feeder{feeder}
    {
        addSubsystemRequirement(&m_feeder);
    }
    void UnjamCommand::initialize()
    {
        m_feeder.unjamOn();
    }
    void UnjamCommand::execute()
    {
    }
    void UnjamCommand::end(bool interrupted)
    {
        m_feeder.unjamOff();
    }
    bool UnjamCommand::isFinished() const
    {
        //Only needs to switch the booster
        return false;
    }
}