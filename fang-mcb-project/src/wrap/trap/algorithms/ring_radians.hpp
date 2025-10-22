#pragma once

#include "wrapped_radians.hpp"

namespace trap::algorithms
{
    /**
     * This allows interfacing with general pid classes
     * when utilizing rotations
     * 
     * All this does is override operator- to use minDifference
     * which is more suitable for pid
     */
    class RingRadians : public WrappedRadians
    {
    public:
        using WrappedRadians::WrappedRadians;

        RingRadians() : WrappedRadians{Radians{0}} {}
        Radians operator-(const WrappedRadians& other) const
        {
            return minDifference(other);
        }
    };
}