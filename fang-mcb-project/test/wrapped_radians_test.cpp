#include "trap/algorithms/wrapped_radians.hpp"
#include <gtest/gtest.h>

using WrappedRadians = trap::algorithms::WrappedRadians;
//The primary use in this codebase is for checking the difference between a target and a desired angle
constexpr double k_pi{WrappedRadians::k_pi};
TEST(differenceTest, wrappedRadians)
{
    const WrappedRadians target{Radians{k_pi * (3.0 / 2.0)}};
    const WrappedRadians current{Radians{k_pi * (0.0)}};
    //The result is that we need to move 90 degrees counterclockwise
    const WrappedRadians expected{Radians{k_pi * (1.0 / 2.0)}};

    const WrappedRadians requiredMotion{current - target};
}