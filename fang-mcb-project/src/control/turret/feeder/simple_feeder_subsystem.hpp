#ifndef FANG_ROBOTICS_MCB_RAIL_TURRET_I_SIMPLE_FEEDER_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_RAIL_TURRET_I_SIMPLE_FEEDER_SUBSYSTEM_HPP

#include "wrap/rail/turret/isimple_feeder.hpp"

#include "tap/control/subsystem.hpp"
#include "tap/drivers.hpp"

namespace fang::turret
{
    /**
     * Provide taproot commands with uniform access to
     * simple feeder subsystem
     */
    class SimpleFeederSubsystem:
        public ISimpleFeeder,
        public tap::control::Subsystem
    {
    public:
        SimpleFeederSubsystem(tap::Drivers& drivers):
            tap::control::Subsystem{&drivers}
        {}

        //Prevent ambiguity conflitcs
        virtual void initialize() = 0;
        virtual ~SimpleFeederSubsystem() {};
    };
}
#endif
