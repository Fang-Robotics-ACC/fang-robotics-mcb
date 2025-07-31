#ifndef FANG_ROBOTICS_MCB_WRAP_TRAP_CONTROL_SUBSYSTEM_EQUIVALENT_HPP
#define FANG_ROBOTICS_MCB_WRAP_TRAP_CONTROL_SUBSYSTEM_EQUIVALENT_HPP
#include "tap/drivers.hpp"
namespace trap::control
{
    /**
     * Allows rail and taproot to mesh susystems more seamlessly
     * without relying on having a subsystem instance.
     * 
     * This allows testing to work better since test instances
     * of classes which inherit from a subsystem or can function as a subsystem
     * (a command must take a IHolonomicSubsystem and not IHolonomicControl due
     * to it needing to register with a subsystem).
     * 
     * The interface must inherit from subsystem, but if it does,
     * then it must have a drivers instance.
     * 
     * There is a cleaner solution: by allowing conversion into a subsystem
     * the interface can provide a command the subsystem for registration
     * but then not require.
     */
    class SubsystemEquivalent
    {
        virtual operator tap::Drivers* () = 0;
    };
}
#endif // WRAP_TRAP_CONTROL_SUBSYSTEM_EQUIVALENT_HPP_
