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
        using WrappedRadians::WrappedRadians;

        Radians operator-(const WrappedRadians& other)
        {
            return minDifference(other);
        }
    };
}