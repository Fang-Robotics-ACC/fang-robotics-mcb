#include "gearbox_repeat_ultra_mk2.hpp"
#include "driver/motor/util/gearbox_speed.hpp"

namespace fang::motor
{
    GearboxRepeatUltraMk2::GearboxRepeatUltraMk2
    (
        Drivers& drivers,
        const Config& config
    ):

        kControllerInputVoltage_{config.controllerInputVoltage},
        kGearRatio_{config.gearRatio},
        kInversionMultiplier_{config.inverted ? -1 : 1}, // Reverse if inverted lol, motor is bidirectional
        vortex_{drivers.pwm, config.pwmData}
    {}

	void GearboxRepeatUltraMk2::setTargetSpeed(const RPM& speed)
    {
        const RPM motorSpeed{shaftToMotorSpeed(speed, kGearRatio_)};
        const double speedPercentage{motorSpeed / kMaxTheoreticalSpeed_};
        vortex_.setSpeed(speedPercentage * kInversionMultiplier_);
    }

    void GearboxRepeatUltraMk2::initialize()
    {
        vortex_.sendArmingSignal();
    }

    void GearboxRepeatUltraMk2::update()
    {
        //TODO: Ramping functionality
    }
}//namespace motor