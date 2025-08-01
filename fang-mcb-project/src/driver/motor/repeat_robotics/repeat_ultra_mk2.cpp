#include "repeat_ultra_mk2.hpp"
#include "driver/motor/util/gearbox_speed.hpp"
#include "system/assert/fang_assert.hpp"

#include "wrap/units/units_alias.hpp"

namespace fang::motor
{
    using namespace units::literals;

    RepeatUltraMk2::RepeatUltraMk2
    (
        Drivers& drivers,
        const Config& config
    ):

        kControllerInputVoltage_{config.controllerInputVoltage},
        kGearRatio_{config.gearRatio},
        kInversionMultiplier_{config.inverted ? -1 : 1}, // Reverse if inverted lol, motor is bidirectional
        vortex_{drivers.pwm, config.pwmData}
    {
        assertConfigValidity(config);
    }

	void RepeatUltraMk2::setTargetSpeed(const RPM& speed)
    {
        const RPM motorSpeed{shaftToMotorSpeed(speed, kGearRatio_)};
        const double speedPercentage{motorSpeed / kMaxTheoreticalSpeed_};
        vortex_.setSpeed(speedPercentage * kInversionMultiplier_);
    }

    void RepeatUltraMk2::initialize()
    {
        vortex_.sendArmingSignal();
    }

    void RepeatUltraMk2::update()
    {
        //TODO: Ramping functionality
    }

    void RepeatUltraMk2::assertConfigValidity(const Config& config)
    {
        FANG_ASSERT(config.gearRatio > 0.0, "Gear ratio cannot cause singularities or flip the directions");
        FANG_ASSERT(config.controllerInputVoltage >= 0.0_V, "Voltage should be positive. Either fix the code or the wiring");
    }
}//namespace motor