#include "ammo_booster_subsystem.hpp"
namespace fang::turret
{

    AmmoBoosterSubsystem::AmmoBoosterSubsystem(Drivers& drivers, const Config& config)
    :   Subsystem{&drivers},
        m_booster{drivers, config}
    {
    }

    void AmmoBoosterSubsystem::initialize()
    {
        m_booster.initialize();
    }

    void AmmoBoosterSubsystem::refresh()
    {
        m_booster.update();
    }

    void AmmoBoosterSubsystem::refreshSafeDisconnect()
    {
        m_booster.autoFireOff();
    }

    void AmmoBoosterSubsystem::autoFireOn()
    {
        m_booster.autoFireOn();
    }

    void AmmoBoosterSubsystem::autoFireOff()
    {
        m_booster.autoFireOff();
    }
}