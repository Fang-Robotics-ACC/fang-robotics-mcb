#ifndef FANG_ROBOTICS_MCB_RAIL_TURRET_I_SIMPLE_FEEDER_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_RAIL_TURRET_I_SIMPLE_FEEDER_SUBSYSTEM_HPP

#include "rail/turret/feeder/isimple_feeder_control.hpp"

#include "tap/control/subsystem.hpp"
#include "tap/drivers.hpp"

namespace rail::turret
{
    /**
     * Provide taproot commands with uniform access to
     * simple feeder subsystem
     */
    class ISimpleFeederSubsystem:
        public ISimpleFeederControl,
        public tap::control::Subsystem
    {
    public:
        ISimpleFeederSubsystem(tap::Drivers& drivers):
            tap::control::Subsystem(&drivers)
        {}
        virtual ~ISimpleFeederSubsystem() {};
    };
}
#endif
