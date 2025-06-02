#ifndef FANG_ROBOTICS_MCB_TRAP_WRAPPED_FLOAT_HPP
#define FANG_ROBOTICS_MCB_TRAP_WRAPPED_FLOAT_HPP
#include "tap/algorithms/wrapped_float.hpp"
namespace trap
{
    namespace algorithms
    {
        template<typename Unit>
        /**
         * This is a wrappedFloat but uses units instead
         * https://aruw.gitlab.io/controls/taproot/api/classtap_1_1algorithms_1_1_wrapped_float.html#exhale-class-classtap-1-1algorithms-1-1-wrapped-float
         */
        class WrappedFloat
        {
        public:
            using TappedFloat = tap::algorithms::WrappedFloat;
            WrappedFloat(Unit value, Unit lowerBound, Unit upperBound)
            : m_wrappedFloat{static_cast<float>(value),static_cast<float>(lowerBound), static_cast<float>(upperBound)}
            { 
            }

            WrappedFloat(const tap::algorithms::WrappedFloat& wrappedFloat)
            : m_wrappedFloat(wrappedFloat.getWrappedValue(), wrappedFloat.getLowerBound(), wrappedFloat.getUpperBound())
            {
            }

            bool operator==(const WrappedFloat& other) const
            {
                return m_wrappedFloat == other.m_wrappedFloat;
            }

            void operator+=(const WrappedFloat& other)
            {
                m_wrappedFloat += other.m_wrappedFloat;
            }

            void operator-=(const WrappedFloat& other) 
            {
                m_wrappedFloat -= other.m_wrappedFloat;
            }

            WrappedFloat operator+(const WrappedFloat& other) const
            {
                return WrappedFloat {m_wrappedFloat + other.m_wrappedFloat};
            }

            WrappedFloat operator-(const WrappedFloat& other) const
            {
                return WrappedFloat {m_wrappedFloat - other.m_wrappedFloat};
            }

            Unit minDifference(const WrappedFloat& other) const
            {
                return Unit{m_wrappedFloat.minDifference(other.m_wrappedFloat.getWrappedValue())};
            }

            Unit minDifference(const Unit& unwrappedValue) const
            {
                return Unit{m_wrappedFloat.minDifference(static_cast<float>(unwrappedValue))};
            }

            void shiftBounds(Unit shiftMagnitude)
            {
                m_wrappedFloat.shiftBounds(static_cast<float>(shiftMagnitude));
            }


            static Unit limitValue(const WrappedFloat& valueToLimit, const Unit min, const Unit max, int* status)
            {
                const float floatValue{TappedFloat::limitValue(valueToLimit.m_wrappedFloat,
                                                         static_cast<float>(min),
                                                         static_cast<float>(max),
                                                        status)};
                return Unit{floatValue};
            }

            static Unit limitValue(const WrappedFloat& valueToLimit, const WrappedFloat& min, const WrappedFloat& max, int* status)
            {
                const float floatValue{TappedFloat::limitValue(valueToLimit.m_wrappedFloat,
                                                         min.m_wrappedFloat,
                                                         max.m_wrappedFloat,
                                                        status)};
                return Unit{floatValue};
            }

            bool withinRange(const WrappedFloat& lowerBound, const WrappedFloat upperBound) const
            {
                return m_wrappedFloat.withinRange(lowerBound.m_wrappedFloat, upperBound.m_wrappedFloat);
            }

            static Unit rangeOverlap(const WrappedFloat& lowerA, const WrappedFloat& upperA,
                                      const WrappedFloat& lowerB, const WrappedFloat& upperB)
            {
                const float floatResult{TappedFloat::rangeOverlap(lowerA.m_wrappedFloat, upperA.m_wrappedFloat, lowerB.m_wrappedFloat, upperB.m_wrappedFloat)};
                return Unit{floatResult};
            }

            inline Unit getUnwrappedValue() const
            {
                return Unit{m_wrappedFloat.getUnwrappedValue()};
            }

            inline Unit getWrappedValue() const
            {
                return Unit{m_wrappedFloat.getWrappedValue()};
            }

            inline void setWrappedValue(const Unit& newValue)
            {
                m_wrappedFloat.setWrappedValue(static_cast<float>(newValue));
            }

            inline void setUnwrappedValue(const Unit& newValue)
            {
                m_wrappedFloat.setUnwrappedValue(static_cast<float>(newValue));
            }

            inline WrappedFloat getNormalized() const
            {
                return WrappedFloat(m_wrappedFloat.getNormalized());
            }

            inline int getRevolutions() const
            {
                return m_wrappedFloat.getRevolutions();
            }

            inline Unit getUpperBound() const
            {
                return Unit{m_wrappedFloat.getUpperBound()};
            }

            inline Unit getLowerBound() const
            {
                return Unit{m_wrappedFloat.getLowerBound()};
            }

        private:
        TappedFloat m_wrappedFloat;
        };
    }
}
#endif 