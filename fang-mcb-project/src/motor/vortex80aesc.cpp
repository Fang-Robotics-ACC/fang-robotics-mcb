#include "vortex80aesc.hpp"
#include "trap/communication/pwm_data.hpp"
#include "pwmconstants.hpp"

#include "modm/architecture/interface/delay.hpp"
#include "modm/math/interpolation/linear.hpp"
#include "modm/container/pair.hpp"
#include "tap/communication/gpio/pwm.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

namespace motor
{
    Vortex80AEsc::Vortex80AEsc(tap::gpio::Pwm& pwm, const trap::gpio::PwmData& pwmData, const Directionality& directionality)
    : m_pwm{pwm}, m_pwmData{pwmData}, m_directionality{directionality}, mk_cyclePeriod{1.0 / pwmData.pinFrequency}
    {
    }
    void Vortex80AEsc::sendArmingSignal()
    {
        switch(m_directionality)
        {
            case Directionality::BIDIRECTIONAL:
                setPulseDuration(mk_bidirectionalArmingSignal);
                break;
            case Directionality::UNIDIRECTIONAL:
                setPulseDuration(mk_unidirectionalArmingSignal);
                break;
        }
    }
    void Vortex80AEsc::armingRoutine()
    {
        sendArmingSignal();
        modm::delay_ms(mk_armingPeriod.to<double>());
    }
    void Vortex80AEsc::setSpeed(double speedRangePercentage)
    {
        setPulseDuration(calculatePeriod(speedRangePercentage));
    }
    void Vortex80AEsc::setPulseDuration(const Microseconds& duration)
    {
        assert(duration <= mk_cyclePeriod && "The pulse duration exceeds cycle period");
        const double dutyCycle{duration / mk_cyclePeriod}; //Self explanatory if you know pwm lol
        pwmWrite(dutyCycle);
    }
    Microseconds Vortex80AEsc::calculatePeriod(double speedRangePercentage) const
    {
        Microseconds period{0};
        switch (m_directionality)
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
        //assert(mk_unidirectionalMin <= speedRangePercentage && speedRangePercentage <= mk_unidirectionalMax && "Unidirectional limit is [0,1]");
        return Microseconds{m_unidirectionalMap.interpolate(speedRangePercentage)};
    }
    Microseconds Vortex80AEsc::calculateBidirectionalPeriod(double speedRangePercentage) const
    {
        //assert(mk_bidirectionalMin <= speedRangePercentage && speedRangePercentage <= mk_bidirectionalMax && "Bidirectional limit is [-1,1]");
        return Microseconds{m_bidirectionalMap.interpolate(speedRangePercentage)};
    }
    void Vortex80AEsc::setDirectionality(const Directionality& directionality)
    {
        m_directionality = directionality;
    }
    Vortex80AEsc::Directionality Vortex80AEsc::getDirectionality() const
    {
        return m_directionality;
    }
    void Vortex80AEsc::pwmWrite(double dutyCycle)
    {
        m_pwm.write(dutyCycle, m_pwmData.pwmPin);
    }
}
