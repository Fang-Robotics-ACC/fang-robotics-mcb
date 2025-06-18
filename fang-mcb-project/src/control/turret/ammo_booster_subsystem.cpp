#include "ammo_booster_subsystem.hpp"
namespace control::turret
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

    void AmmoBoosterSubsystem::autoFireOn()
    {
        m_booster.autoFireOn();
    }

    void AmmoBoosterSubsystem::autoFireOff()
    {
        m_booster.autoFireOff();
    }
}