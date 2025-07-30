#ifndef FANG_ROBOTICS_MCB_RAIL_TURRET_I_SIMPLE_FEEDER_SUBSYSTEM_CONTROL_HPP
#define FANG_ROBOTICS_MCB_RAIL_TURRET_I_SIMPLE_FEEDER_SUBSYSTEM_CONTROL_HPP
#include "wrap/rail/drivers.hpp"
#include "tap/control/subsystem.hpp"
#include "rail/turret/feeder/isimple_feeder_control.hpp"
namespace rail::turret
{
    class ISimpleFeederSubsystem:
        virtual public tap::control::Subsystem,
        virtual public ISimpleFeederControl
    {
    public:
        //Trivial hack
        ISimpleFeederSubsystem(Drivers& drivers):
            tap::control::Subsystem(&drivers)
        {}
        virtual ~ISimpleFeederSubsystem() {};
    };
}
#endif
