#include "feeder_subsystem.hpp"
namespace control::turret
{

    FeederSubsystem::FeederSubsystem(Drivers& drivers, const Config& config)
    :   Subsystem{&drivers},
        m_feeder{drivers, config}
    {
    }

    void FeederSubsystem::initialize()
    {
        m_feeder.initialize();
    }

    void FeederSubsystem::refresh()
    {
        m_feeder.update();
    }
}