#include "vortex_80a_esc.hpp"
#include "communication/gpio/pwm/pwm_info.hpp"

#include "wrap/trap/communication/pwm_data.hpp"

#include "modm/architecture/interface/delay.hpp"
#include "modm/math/interpolation/linear.hpp"
#include "modm/container/pair.hpp"

#include "tap/communication/gpio/pwm.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

namespace fang::motor
{

    const math::CoolLerp Vortex80AEsc::kBidirectionalMap_{kBidirectionalPoint1_, kBidirectionalPoint2_};
    const math::CoolLerp Vortex80AEsc::kUnidirectionalMap_{kUnidirectionalPoint1_, kUnidirectionalPoint2_};

    Vortex80AEsc::Vortex80AEsc(tap::gpio::Pwm& pwm, const trap::gpio::PwmData& pwmData, const Directionality& directionality)
    : pwmDriver_{pwm}, pwmData_{pwmData}, kDirectionality_{directionality}, kCyclePeriod_{1.0 / pwmData.pinFrequency}
    {
    }
    void Vortex80AEsc::sendArmingSignal()
    {
        switch(kDirectionality_)
        {
            case Directionality::BIDIRECTIONAL:
                setPulseDuration(kBidirectionalArmingSignal_);
                break;
            case Directionality::UNIDIRECTIONAL:
                setPulseDuration(kUnidirectionalArmingSignal_);
                break;
        }
    }
    void Vortex80AEsc::armingRoutine()
    {
        sendArmingSignal();
        modm::delay_ms(kArmingPeriod_.to<double>());
    }
    void Vortex80AEsc::setSpeed(double speedRangePercentage)
    {
        setPulseDuration(calculatePeriod(speedRangePercentage));
    }
    void Vortex80AEsc::setPulseDuration(const Microseconds& duration)
    {
        assert(duration <= kCyclePeriod_ && "The pulse duration exceeds cycle period");
        const double dutyCycle{duration / kCyclePeriod_}; //Self explanatory if you know pwm lol
        pwmWrite(dutyCycle);
    }
    Microseconds Vortex80AEsc::calculatePeriod(double speedRangePercentage) const
    {
        Microseconds period{0};
        switch (kDirectionality_)
        {
            case Directionality::BIDIRECTIONAL:
                period = calculateBidirectionalPeriod(speedRangePercentage);
                break;

            case Directionality::UNIDIRECTIONAL:
                period = calculateUnidirectionalPeriod(speedRangePercentage);
            break;
        }
        return period;
    }
    Microseconds Vortex80AEsc::calculateUnidirectionalPeriod(double speedRangePercentage) const
    {
        //assert(kUnidirectionalMin_ <= speedRangePercentage && speedRangePercentage <= kUnidirectionalMax_ && "Unidirectional limit is [0,1]");
        return Microseconds{kUnidirectionalMap_.interpolate(speedRangePercentage)};
    }
    Microseconds Vortex80AEsc::calculateBidirectionalPeriod(double speedRangePercentage) const
    {
        //assert(kBidirectionalMin_ <= speedRangePercentage && speedRangePercentage <= kBidirectionalMax_ && "Bidirectional limit is [-1,1]");
        return Microseconds{kBidirectionalMap_.interpolate(speedRangePercentage)};
    }
    void Vortex80AEsc::setDirectionality(const Directionality& directionality)
    {
        kDirectionality_ = directionality;
    }
    Directionality Vortex80AEsc::getDirectionality() const
    {
        return kDirectionality_;
    }
    void Vortex80AEsc::pwmWrite(double dutyCycle)
    {
        pwmDriver_.write(dutyCycle, pwmData_.pwmPin);
    }
}
