#include "vortex80aesclogic.hpp"
#include "pwmconstants.hpp"
#include <cmath>
#include "modm/math/interpolation/linear.hpp"
#include "modm/container/pair.hpp"
#include "cassert"
#include <iostream>

namespace logic 
{
    namespace motors
    {

        Vortex80AEscLogic::Vortex80AEscLogic(const Directionality& directionality, const Hertz& pinFrequency):
                                             m_directionality{directionality}, m_pinFrequency{pinFrequency}
        {
        }

        double Vortex80AEscLogic::calculateDutyCycle (double speedRangePercentage)
        {
            double dutyCycle{0};
            switch (m_directionality)
            {
                case Directionality::BIDIRECTIONAL:
                    dutyCycle = calculateBidirectionalDutyCycle(speedRangePercentage);
                    break;
                
                case Directionality::UNIDIRECTIONAL:
                    dutyCycle = calculateUnidirectionalDutyCycle(speedRangePercentage); 
            }
            return dutyCycle;
        }

        double Vortex80AEscLogic::calculateUnidirectionalDutyCycle(double speedRangePercentage)
        {
            assert(0.0 <= speedRangePercentage && speedRangePercentage <= 1.0 && "Unidirectional limit is [0,1]");
            return adaptedDutyCycle(speedRangePercentage);
        }

        double Vortex80AEscLogic::calculateBidirectionalDutyCycle(double speedRangePercentage)
        {
            assert(mk_bidirectionalMin <= speedRangePercentage && speedRangePercentage <= mk_bidirectionalMax && "Unidirectional limit is [-1,1]");
            // Manual lerp, todo: figure out modm's Linear class
            // -1 needs to be mapped to 0, 1 needs to be mapped to -1
            //The maximum is 1 and the minimum is -1, I'm just being pedantic to overly document stuff
            const double bidirectionalRange {mk_bidirectionalMax - mk_bidirectionalMin};
            // The minimum value is -1, but if we shift it up by one, the new minimum is 0
            // We subtract by the min because it is less than 0 and must be for bidirectional controls
            const double offsettedPercentage{speedRangePercentage - mk_bidirectionalMin};
            assert(bidirectionalRange == 2.0);
            const double rangePercentage{offsettedPercentage / bidirectionalRange};
            std::cout << rangePercentage;

            //Santiy check. This should never be violated. If it does, then someone messed with the code wrong...
            assert(config::pwm::k_pwmDutyMin <= rangePercentage && rangePercentage <= config::pwm::k_pwmDutyMax && "rangePercentage out of bounds");
            
            
            return adaptedDutyCycle(rangePercentage);
        }

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