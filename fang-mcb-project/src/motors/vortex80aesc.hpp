#ifndef VORTEX_80A_ESC_LOGIC_H_LSDJKFLSKEFJF_YEET
#define VORTEX_80A_ESC_LOGIC_H_LSDJKFLSKEFJF_YEET
#include "unitaliases.hpp"
#include "directionality.hpp"

namespace logic
{
    namespace motors
    {
        /**
         * Driver for the Vortex80AEsc involving sending various signals and speed ranges.
         */
        class Vortex80AEsc
        {
        public:
            using Directionality = data::motors::Directionality;
            Vortex80AEsc(const Directionality& directionality = Directionality::BIDIRECTIONAL, const Hertz& pinFrequency = Hertz{500});
            double calculateDutyCycle (double speedRangePercentage);
            /**
             * 
             * Returns a duty cycle from
             * [0,1] (percentage in decimal form)
             * 
             * The Vortex motor controller expects
             * a pulse from 1ms to 2ms with 1ms
             * corresponding to the lowest possible input, 0 and
             * 2ms corresponding to the highest input, 1.
             * 
             * In unidirectional, the speed percentage range
             * is [0,1]
             * Therefore, 0.5 would correspond to a motor moving
             * 50% of the maximum speed
             * 
             * In bidirectional, the range is [-1,1]
             * Therefore, 0.5 would correspond to a motor being still.
             * 0 would correspond to a motor running at full speed in reverse
             * Frequencies with a period lower than 2ms will not work on this
             * controller. The required duty cycle would be greater than 1.
             * In other words, anything greater than 500 Hz since you need to
             * have a pulse at least 2ms long.
             */
            double adaptedDutyCycle(double rangePercentage, Hertz pinFrequency);
            double adaptedDutyCycle(double rangePercentage);
            void setDirectionality(const Directionality& directionality);
            Directionality getDirectionality() const;
            void setPinFrequency(const Hertz& pinFrequency);
            Hertz getPinFrequency() const;
        private:
            // Note that in bidirectional mode, the minimum period would
            // correspond to the motor going in full speed reverse
            // But in unidirectional mode, it would mean a still motor
            const Milliseconds mk_maxRangePeriod {2.0};
            const Milliseconds mk_minRangePeriod {1.0};
            const double mk_bidirectionalMin {-1.0};
            const double mk_bidirectionalMax {1.0};

            const double mk_uniDirectionalMin {0.0};
            const double mk_uniDirectionalMax {1.0};

            Hertz m_pinFrequency;
            Directionality m_directionality;

            double calculateUnidirectionalDutyCycle(double speedRangePercentage);
            double calculateBidirectionalDutyCycle(double speedRangePercentage);
        };
    }
}
#endif