#ifndef FANG_ROBOTICS_MCB_TURRET_SUBSYSTEM_BLUEPRINT_SIMPLE_FEEDER_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_TURRET_SUBSYSTEM_BLUEPRINT_SIMPLE_FEEDER_SUBSYSTEM_HPP
#include "simple_feeder_subsystem.hpp"
#include "wrap/rail/rail_turret_aliases.hpp"

namespace control::turret
{

    SimpleFeederSubsystem::SimpleFeederSubsystem(Drivers& drivers, ISimpleFeeder& feeder, const Config& config):
        Subsystem{&drivers},
        feeder_{feeder},
        heatLimiter_{drivers.refSerial, {config.heatLimiterConfig}}
    {
    }

    void SimpleFeederSubsystem::initialize()
    {
        feeder_.initialize();
    }

    void SimpleFeederSubsystem::refresh()
    {
        if(heatLimiter_.stopRecommended())
        {
            feeder_.feedOff();
        }
        feeder_.update();
    }

    void SimpleFeederSubsystem::refreshSafeDisconnect()
    {
        feeder_.feedOff();
    }
    void SimpleFeederSubsystem::feedOn()
    {
        //Prevent from new feeding sequnces from being triggered
        if(!heatLimiter_.stopRecommended())
        {
            feeder_.feedOn();
        }
    }

    void SimpleFeederSubsystem::feedOff()
    {
        feeder_.feedOff();
    }

    void SimpleFeederSubsystem::unjamOn()
    {
        feeder_.unjamOn();
    }

    void SimpleFeederSubsystem::unjamOff()
    {
        feeder_.unjamOff();
    }
}
#endif