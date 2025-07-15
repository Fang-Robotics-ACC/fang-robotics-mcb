#include "feeder_subsystem.hpp"
namespace control::turret
{

    FeederSubsystem::FeederSubsystem(Drivers& drivers, const Config& config):
        ISimpleFeederSubsystemControl{drivers},
        Subsystem{&drivers},
        m_feeder{drivers, config.feederConfig},
        m_heatLimiter{drivers.refSerial, {config.heatLimiterConfig}}
    {
    }

    void FeederSubsystem::initialize()
    {
        m_feeder.initialize();
    }

    void FeederSubsystem::refresh()
    {
        if(m_heatLimiter.stopRecommended())
        {
            m_feeder.feedOff();
        }
        m_feeder.update();
    }

    void FeederSubsystem::refreshSafeDisconnect()
    {
        m_feeder.feedOff();
    }
    void FeederSubsystem::feedOn()
    {
        //Prevent new feeding sequnces from being triggered
        if(!m_heatLimiter.stopRecommended())
        {
            m_feeder.feedOn();
        }
    }

    void FeederSubsystem::feedOff()
    {
        m_feeder.feedOff();
    }

    void FeederSubsystem::unjamOn()
    {
        m_feeder.unjamOn();
    }

    void FeederSubsystem::unjamOff()
    {
        m_feeder.unjamOff();
    }
}