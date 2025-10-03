#pragma once
#include "smooth_pid.hpp"
namespace trap::algorithms
{
    template<typename MainError, typename IntermediateError, typename Output>
    /**
     * Cascading PID
     * 
     * MainError is the type for the beginning and main targeted value
     * IntermediateError is the type that is in the middl
     * 
     * e.g. Radians which then output a target RPM which outputs an abstract Motoroutput
     * 
     * The main target is the radians, but the target for the intermediate error
     * is give by the first PID
     */
    class DualPid
    {
    public:
    private:
    };
}