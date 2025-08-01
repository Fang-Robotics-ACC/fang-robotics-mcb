#include "repeat_ultra_mk2.hpp"
#include "units.h"

#include "wrap/trap/communication/pwm_data.hpp"
#include "tap/algorithms/math_user_utils.hpp"

#include <algorithm>
#include <cassert>

using namespace units::literals;

namespace fang::motor
{

    RepeatUltraMk2::RepeatUltraMk2(Drivers& drivers, const Config& config):
        RepeatUltraMk2
        (
            drivers,
            config.controllerInputVoltage,
            config.pwmData.pwmPin,
            config.pwmData.pinFrequency,
            config.directionality,
            config.inverted
        )
    {
    }
    RepeatUltraMk2::RepeatUltraMk2(
        tap::Drivers& drivers,
        const Volts& controllerInputVoltage,
        tap::gpio::Pwm::Pin pwmPin,
        const Hertz& pinFrequency,
        Directionality directionality,
        bool inverted)
        :
        kControllerInputVoltage_{controllerInputVoltage},
        kMaxTheoreticalSpeed_{kKv * kControllerInputVoltage_},
        inversionMultiplier_{inverted && (directionality == Directionality::BIDIRECTIONAL)? int8_t{-1}: int8_t{1}},
        vortex_{drivers.pwm, trap::gpio::PwmData{pwmPin, pinFrequency}, directionality}
    {
    }

	void RepeatUltraMk2::setTargetSpeed(const RPM& speed)
    {
        const double speedPercentage{speed * inversionMultiplier_ / kMaxTheoreticalSpeed_};
        vortex_.setSpeed(speedPercentage);
    }

    /**
     * The initialization needs to have an arming signal sent for
     * 1-2 seconds. It will be left up to the caller on how to 
     * ensure the delay.
     */
    void RepeatUltraMk2::initialize()
    {
        vortex_.sendArmingSignal();
    }

    void RepeatUltraMk2::update()
    {
    }

}//namespace motor