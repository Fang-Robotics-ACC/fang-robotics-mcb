#include "repeat_ultra_mk2.hpp"
#include "driver/motor/util/gearbox_speed.hpp"
#include "system/assert/fang_assert.hpp"

#include "wrap/units/units_alias.hpp"
#include "tap/algorithms/math_user_utils.hpp"

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
        speedRamp_{0_rpm, config.rampSpeed},
        vortex_{drivers.pwm, config.pwmData}
    {
        assertConfigValidity(config);
    }

	void RepeatUltraMk2::setTargetSpeed(const RPM& speed)
    {
        speedRamp_.setTarget(speed);
    }

    void RepeatUltraMk2::initialize()
    {
        vortex_.sendArmingSignal();
    }

    void RepeatUltraMk2::update()
    {
        speedRamp_.update();
        syncVotex();
    }

    void RepeatUltraMk2::syncVotex()
    {
        const RPM kSpeed{speedRamp_.getValue()};
        const RPM kMotorSpeed{shaftToMotorSpeed(kSpeed, kGearRatio_)};
        const double kSpeedPercentage{kMotorSpeed / kMaxTheoreticalSpeed_};

        //There are slight cases where the rounding errors go above one
        //Max and min are %100 and negative %100, normally i'd shun magic
        //numbers but these are pretty obvious
        const double kClampedSpeed{tap::algorithms::limitVal<double>(kSpeedPercentage, -1.0, 1.0)};
        vortex_.setSpeed(kClampedSpeed * kInversionMultiplier_);
    }

    void RepeatUltraMk2::assertConfigValidity(const Config& config)
    {
        FANG_ASSERT(config.gearRatio > 0.0, "Gear ratio cannot cause singularities or flip the directions");
        FANG_ASSERT(config.controllerInputVoltage >= 0.0_V, "Voltage should be positive. Either fix the code or the wiring");
    }
}//namespace motor