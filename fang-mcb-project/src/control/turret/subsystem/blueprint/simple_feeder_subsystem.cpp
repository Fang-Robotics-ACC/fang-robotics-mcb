#ifndef FANG_ROBOTICS_MCB_TURRET_SUBSYSTEM_BLUEPRINT_SIMPLE_FEEDER_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_TURRET_SUBSYSTEM_BLUEPRINT_SIMPLE_FEEDER_SUBSYSTEM_HPP
#include "simple_feeder_subsystem.hpp"
#include "wrap/rail/rail_turret_aliases.hpp"

namespace control::turret
{

    BasicFeederSubsystem::BasicFeederSubsystem(Drivers& drivers, ISimpleFeeder& feeder, const Config& config):
        Subsystem{&drivers},
        feeder_{feeder},
        heatLimiter_{drivers.refSerial, {config.heatLimiterConfig}}
    {
    }

    void BasicFeederSubsystem::initialize()
    {
        feeder_.initialize();
    }

    void BasicFeederSubsystem::refresh()
    {
        if(heatLimiter_.stopRecommended())
        {
            feeder_.feedOff();
        }
        feeder_.update();
    }

    void BasicFeederSubsystem::refreshSafeDisconnect()
    {
        feeder_.feedOff();
    }
    void BasicFeederSubsystem::feedOn()
    {
        //Prevent from new feeding sequnces from being triggered
        if(!heatLimiter_.stopRecommended())
        {
            feeder_.feedOn();
        }
    }

    void BasicFeederSubsystem::feedOff()
    {
        feeder_.feedOff();
    }

    void BasicFeederSubsystem::unjamOn()
    {
        feeder_.unjamOn();
    }

    void BasicFeederSubsystem::unjamOff()
    {
        feeder_.unjamOff();
    }
}
#endif