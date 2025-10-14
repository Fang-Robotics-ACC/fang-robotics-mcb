#pragma once
#include "driver/drivers.hpp"
#include "dji_motor.hpp"

#include "tap/motor/dji_motor.hpp"

namespace trap::motor
{
    /**
     * Driver for a Dji M3508 motor controlled by a
     * Dji C620 controller
     */
    class DjiGM6020 : public DjiMotor
    {
    public:
        // Inheriting constructors :D
        using DjiMotor::DjiMotor;
        constexpr static DjiMotorOutput kMaxOutput{tap::motor::DjiMotor::MAX_OUTPUT_GM6020};
    };
}