#ifndef FANG_ROBOTICS_MCB_WRAPPED_RADIANS_HPP
#define FANG_ROBOTICS_MCB_WRAPPED_RADIANS_HPP
#include "trap/algorithms/wrapped_float.hpp"
#include "unitaliases.hpp"
#include <cmath>
namespace trap
{
    namespace algorithms 
    {
        class WrappedRadians : public WrappedFloat<Radians>
        {
        public:
            WrappedRadians(const Radians& value);

            WrappedRadians(const WrappedFloat<Radians>& value);
            static constexpr double k_pi{M_PI};
            static constexpr double k_tau{M_PI * 2};
        private:
            static constexpr Radians mk_minimumValue{0.0};
            static constexpr Radians mk_maximumValue{k_tau};
        };
    }
}
#endif