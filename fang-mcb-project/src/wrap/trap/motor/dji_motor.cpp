#include "dji_motor.hpp"

#include <cassert>

namespace trap::motor
{
    DjiMotor::DjiMotor(Drivers& drivers, const Config& config)
        :
        DjiMotor
        {
            drivers,
            config.motorId,
            config.canBus,
            config.name,
            config.inverted,
            config.externalEncoderGearRatio,
            config.currentControl
        }
    {
    }

    DjiMotor::DjiMotor
        (
            Drivers& drivers,
            tap::motor::MotorId motorId,
            tap::can::CanBus canBus,
            const char* name,
            bool inverted,
            double externalEncoderGearRatio,
            bool currentControl
        )
        :
        djiMotor_
        {
            &drivers, 
            motorId,
            canBus, 
            inverted,
            name, 
            currentControl, 
            externalEncoderGearRatio
        } //Gear ratio is for extern encoder, causes glitches if non-zero with no external encoder
    {
    }

    /// @brief  left blank
    void DjiMotor::update()
    {
    }

    void DjiMotor::initialize()
    {
        djiMotor_.initialize();
    }

	void DjiMotor::setDesiredOutput(const DjiMotorOutput& output)
    {
        djiMotor_.setDesiredOutput(output);
    }

    void DjiMotor::setTargetOutput(const DjiMotorOutput& desiredOutput)
    {
        setDesiredOutput(desiredOutput);
    }

    bool DjiMotor::isMotorOnline() const
    {
        return djiMotor_.isMotorOnline();
    }

    Celsius DjiMotor::getTemperature() const
    {
        return Celsius{djiMotor_.getTemperature()};
    }

    tap::can::CanBus DjiMotor::getCanBus() const
    {
        return djiMotor_.getCanBus();
    }

    const char* DjiMotor::getName() const
    {
        return djiMotor_.getName();
    }
}
