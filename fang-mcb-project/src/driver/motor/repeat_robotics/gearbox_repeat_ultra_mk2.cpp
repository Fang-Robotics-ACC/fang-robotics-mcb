#include "gearbox_repeat_ultra_mk2.hpp"
#include "driver/motor/util/gearbox_speed.hpp"

namespace fang::motor
{
    GearboxRepeatUltraMk2::GearboxRepeatUltraMk2
    (
        Drivers& drivers,
        const Config& config
    ):
        RepeatUltraMk2
        (
            drivers,
            RepeatUltraMk2::Config
            {
                config.controllerInputVoltage,
                config.pwmData,
                config.inverted
            }
        ),
        kGearRatio_{config.gearRatio}
    {
    }

	void GearboxRepeatUltraMk2::setTargetSpeed(const RPM& speed)
    {
        RepeatUltraMk2::setTargetSpeed(shaftToMotorSpeed(speed, kGearRatio_));
    }
}//namespace motor