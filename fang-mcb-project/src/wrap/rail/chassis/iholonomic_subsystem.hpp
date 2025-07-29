#ifndef FANG_ROBOTICS_MCB_WRAP_RAIL_CHASSIS_I_HOLONOMIC_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_WRAP_RAIL_CHASSIS_I_HOLONOMIC_SUBSYSTEM_HPP
#include "iholonomic_control.hpp"
#include "driver/drivers.hpp"
#include "tap/control/subsystem.hpp"

namespace fang::chassis
{
    class IHolonomicSubsystem:
        virtual public IHolonomicControl,
        virtual public tap::control::Subsystem
    {
    public:
        virtual ~IHolonomicSubsystem() {};
    };
}
#endif