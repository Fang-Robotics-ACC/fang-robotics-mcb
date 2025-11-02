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
        DjiGM6020(Drivers& drivers, const Config& config):
            DjiMotor{
                drivers,
                static_cast<tap::motor::MotorId>(static_cast<int>(config.motorId) + kGM6020CANAddressOffset),
                config.canBus,
                config.name,
                config.inverted,
                config.externalEncoderGearRatio,
                config.currentControl
            }
        {
        }

        constexpr static DjiMotorOutput kMaxOutput{tap::motor::DjiMotor::MAX_OUTPUT_GM6020};
        static constexpr int kGM6020CANAddressOffset{4};
    };
}