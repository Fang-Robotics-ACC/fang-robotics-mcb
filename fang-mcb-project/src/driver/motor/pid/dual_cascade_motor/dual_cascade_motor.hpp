#pragma once
#include "wrap/rail/motor/ioutput_motor.hpp"
namespace fang::motor
{
    /**
     * Template parameters:
     * Output - the output motor it accepts
     * Control - the type used for controlling
     * Intermediate - the type used in between controlling and outputting
     * (2nd pid)
     */
    template <typename Output, typename Control, typename Intermediate>
    class DualCascadeMotor : public IOutputMotor<Output>
    {

    };
}