#pragma once
#include "driver/drivers.hpp"
#include "dji_motor.hpp"

#include "tap/motor/dji_motor.hpp"

namespace trap::motor
{
    class DjiM3508 : public DjiMotor
    {
    public:
        // Inheriting constructors :D
        using DjiMotor::DjiMotor;
        constexpr static DjiMotorOutput kMaxOutput{tap::motor::DjiMotor::MAX_OUTPUT_C620};
    };
}