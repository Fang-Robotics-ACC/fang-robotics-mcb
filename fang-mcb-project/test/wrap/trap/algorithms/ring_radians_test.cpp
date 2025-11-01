#include "wrap/trap/algorithms/ring_radians.hpp"
#include <gtest/gtest.h>

namespace trap::algorithms
{
    //The primary use in this codebase is for checking the difference between a target and a desired angle
    constexpr double k_pi{RingRadians::k_pi};
    TEST(counterClockwiseTargetTest, wrappedRadians)
    {
        const RingRadians current{Radians{k_pi * (0.0)}};

        const RingRadians target{Radians{k_pi * (3.0 / 2.0)}};
        //The result is that we need to move 90 degrees counterclockwise
        const Radians expected{-k_pi * (1.0 / 2.0)};

        const Radians requiredMotion{target - current};
        EXPECT_FLOAT_EQ(expected.to<float>(), requiredMotion.to<float>());
    }

    TEST(clockwiseTargetTest, wrappedRadians)
    {
        const RingRadians target{Radians{k_pi * (0.0 / 2.0)}};
        const RingRadians current{Radians{k_pi * (1.0 / 2.0)}};
        //The result is that we need to move 90 degrees counterclockwise
        const RingRadians expected{Radians{-k_pi * (1.0 / 2.0)}};

        const RingRadians requiredMotion{target - current};
        EXPECT_FLOAT_EQ(expected.getWrappedValue().to<float>(), requiredMotion.getWrappedValue().to<float>());
    }
}
