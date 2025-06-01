#include "vortex80aesc.hpp"
#include "trap/communication/pwm_data.hpp"
#include "pwmconstants.hpp"

#include "modm/math/interpolation/linear.hpp"
#include "modm/container/pair.hpp"
#include "tap/communication/gpio/pwm.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

namespace logic 
{
    namespace motors
    {

        Vortex80AEsc::Vortex80AEsc(tap::gpio::Pwm& pwm, const trap::gpio::PwmData& pwmData, const Directionality& directionality)
        : m_pwm{pwm}, m_pwmData{pwmData}, m_directionality{directionality}, mk_cyclePeriod{1.0 / pwmData.pinFrequency}
        {
        }

        void Vortex80AEsc::setPulseDuration(const Microseconds& duration)
        {
            assert(duration >= mk_cyclePeriod && "The pulse duration exceeds cycle period");
            const double dutyCycle{duration / mk_cyclePeriod}; //Self explanatory if you know pwm lol
            pwmWrite(dutyCycle);
        }

        double Vortex80AEsc::calculateDutyCycle (double speedRangePercentage)
        {
            double dutyCycle{0};
            switch (m_directionality)
            {
                case Directionality::BIDIRECTIONAL:
                    dutyCycle = calculateBidirectionalPeriod(speedRangePercentage);
                    break;
                
                case Directionality::UNIDIRECTIONAL:
                    dutyCycle = calculateUnidirectionalDutyCycle(speedRangePercentage); 
            }
            return dutyCycle;
        }

        double Vortex80AEsc::calculateUnidirectionalDutyCycle(double speedRangePercentage)
        {
            assert(0.0 <= speedRangePercentage && speedRangePercentage <= 1.0 && "Unidirectional limit is [0,1]");
            return adaptedDutyCycle(speedRangePercentage);
        }

        Microseconds Vortex80AEsc::calculateBidirectionalPeriod(double speedRangePercentage)
        {
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

        double Vortex80AEsc::adaptedDutyCycle(double rangePercentage, Hertz pinFrequency)
        {
            // rawDutyCycle will range between 0 and 1
            // 0.50 will correspond to a 1ms pulse (minimum) assuming the pin is set to a period of 2ms
            // 1 will correspond to a 2ms pulse.
            // By dividing the total by 2. It results in the maximum being 0.5
            // Adding the result to 0.5f will shift the minimum to 0.5 and the maximum to 1
            const Milliseconds pinPeriod {1.0 / pinFrequency};
            const double maxDutyCycle{mk_maxRangePeriod / pinPeriod};
            const double minDutyCycle{mk_minRangePeriod / pinPeriod};

            return std::lerp(minDutyCycle, maxDutyCycle, rangePercentage);
        }

        double Vortex80AEsc::adaptedDutyCycle(double rangePercentage)
        {
            return adaptedDutyCycle(rangePercentage, m_pwmData.pinFrequency);
        }

        void Vortex80AEsc::pwmWrite(double dutyCycle)
        {
            m_pwm.write(dutyCycle, m_pwmData.pwmPin);
        }
    }
}