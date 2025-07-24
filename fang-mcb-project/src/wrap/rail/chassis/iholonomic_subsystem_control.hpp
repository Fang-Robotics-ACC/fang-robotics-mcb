#ifndef FANG_ROBOTICS_MCB_WRAP_RAIL_CHASSIS_I_HOLONOMIC_SUBSYSTEM_CONTROL_HPP
#define FANG_ROBOTICS_MCB_WRAP_RAIL_CHASSIS_I_HOLONOMIC_SUBSYSTEM_CONTROL_HPP
#include "iholonomic_control.hpp"
#include "tap/control/subsystem.hpp"

namespace fang::chassis
{
    class IHolonomicSubsystemControl:
        virtual public IHolonomicControl,
        virtual public tap::control::Subsystem
    {
    public:
        virtual ~IHolonomicSubsystemControl() {};
    };
}
#endif