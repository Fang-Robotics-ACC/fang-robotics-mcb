#include "vortex80aesclogic.hpp"
#include <cmath>
#include "modm/math/interpolation/linear.hpp"
#include "modm/container/pair.hpp"

namespace logic 
{
    namespace motors
    {

        void Vortex80AEscLogic::setDirectionality(const Directionality& directionality)
        {
            m_directionality = directionality;
        }

        Vortex80AEscLogic::Directionality Vortex80AEscLogic::getDirectionality() const
        {
            return m_directionality;
        }

        double Vortex80AEscLogic::adaptedDutyCycle(double rangePercentage, Hertz pinFrequency)
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

        double Vortex80AEscLogic::adaptedDutyCycle(double rangePercentage)
        {
            return adaptedDutyCycle(rangePercentage, m_pinFrequency);
        }

        void Vortex80AEscLogic::setPinFrequency(const Hertz& pinFrequency)
        {
            m_pinFrequency = pinFrequency;
        }

        Hertz Vortex80AEscLogic::getPinFrequency() const
        {
            return m_pinFrequency;
        }
    }
}