#include "activate_booster_command.hpp"
#include "tap/algorithms/math_user_utils.hpp"

namespace fang::turret
{
    using namespace units::literals;
    ActivateBoosterCommand::ActivateBoosterCommand(AmmoBoosterSubsystem& booster)
    :   m_booster{booster}
    {
        addSubsystemRequirement(&m_booster);
    }

    void ActivateBoosterCommand::initialize()
    {
        m_booster.autoFireOn();
    }

    void ActivateBoosterCommand::execute()
    {
    }

    void ActivateBoosterCommand::end(bool interrupted)
    {
        m_booster.autoFireOff();
    }

    bool ActivateBoosterCommand::isFinished() const
    {
        //Will be yoinked by the hold command mapping :P
        return false;
    }
}