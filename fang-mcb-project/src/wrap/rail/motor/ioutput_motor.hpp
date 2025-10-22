#pragma once
#include "rail/motor/ioutput_motor.hpp"
namespace fang::motor
{
    // This is left generic due to different motors using different types
    template<typename Output>
    using IOutputMotor = rail::motor::IOutputMotor<Output>;
}