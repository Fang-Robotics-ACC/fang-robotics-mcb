#include "wrapped_radians.hpp"
#include "wrap/units/units_alias.hpp"

namespace trap
{
    namespace algorithms
    {
        WrappedRadians::WrappedRadians(double value) : WrappedRadians{Radians{value}}
        {
        }

        WrappedRadians::WrappedRadians(const Radians& value) : WrappedFloat<Radians>(value, mk_minimumValue, mk_maximumValue)
        {
        }

        WrappedRadians::WrappedRadians(const WrappedFloat<Radians>& value) : WrappedRadians(value.getWrappedValue())
        {
        }
    }
}