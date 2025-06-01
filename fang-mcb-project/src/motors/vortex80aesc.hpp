#ifndef FANG_ROBOTICS_MCB_VORTEX_80A_ESC_LOGIC_H
#define FANG_ROBOTICS_MCB_VORTEX_80A_ESC_LOGIC_H
#include "unitaliases.hpp"
#include "directionality.hpp"

#include "util/math/cool_lerp.hpp"
#include "data/vector2d.hpp"

#include "wrap/trap/communication/pwm_data.hpp"

#include "tap/communication/gpio/pwm.hpp"

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
            Vortex80AEsc(tap::gpio::Pwm& pwm, const trap::gpio::PwmData& pwmData, const Directionality& directionality = Directionality::BIDIRECTIONAL);
            /**
             * This is how long the pwm signal stays high each cycle.
             * You snhould not exceed the cycle period.
             */
            void setPulseDuration(const Microseconds& duration);
            void setDirectionality(const Directionality& directionality);
            Directionality getDirectionality() const;
        private:
            Microseconds calculatePeriod (double speedRangePercentage);
            void pwmWrite(double dutyCycle);
            tap::gpio::Pwm& m_pwm;
            trap::gpio::PwmData m_pwmData;
            const Microseconds mk_cyclePeriod;
            // Note that in bidirectional mode, the minimum period would
            // correspond to the motor going in full speed reverse
            // But in unidirectional mode, it would mean a still motor
            const Milliseconds mk_maxRangePeriod {2.0};
            const Milliseconds mk_minRangePeriod {1.0};
            const double mk_bidirectionalMin {-1.0};
            const double mk_bidirectionalMax {1.0};

            const double mk_unidirectionalMin {0.0};
            const double mk_unidirectionalMax {1.0};

            Directionality m_directionality;

            //Map speed range percentage of -1.0 to 1000 us
            const math::CoolLerp::Vector2D mk_bidirectionalPoint1{-1.0, 1000.0};
            //Map speed rnage percentage of 1.0 to 2000 us
            const math::CoolLerp::Vector2D mk_bidirectionalPoint2{1.0, 2000.0};
            math::CoolLerp m_bidirectionalMap{mk_bidirectionalPoint1, mk_bidirectionalPoint2};

            //Map speed range percentage of 0.0 to 1000 us
            const math::CoolLerp::Vector2D mk_unidirectionalPoint1{0.0, 1000.0};
            //Map speed rnage percentage of 1.0 to 2000 us
            const math::CoolLerp::Vector2D mk_unidirectionalPoint2{1.0, 2000.0};
            math::CoolLerp m_unidirectionalMap{mk_unidirectionalPoint1, mk_unidirectionalPoint2};

            Microseconds calculateUnidirectionalPeriod(double speedRangePercentage);
            Microseconds calculateBidirectionalPeriod(double speedRangePercentage);
        };
    }
}
#endif