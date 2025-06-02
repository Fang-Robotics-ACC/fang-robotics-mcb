#include "trap/algorithms/wrapped_float.hpp"
#include "tap/algorithms/wrapped_float.hpp"

#include "unitaliases.hpp"

#include <gtest/gtest.h>

#include <math.h>
using WrappedFloat = trap::algorithms::WrappedFloat<Degrees>;
using TappedFloat = tap::algorithms::WrappedFloat;
using namespace units::literals;

constexpr double k_pi = M_PI;
constexpr double k_tau = k_pi * 2;
TEST(equalOperator, wrappedFloat)
{
    WrappedFloat wrapped{0_deg, 0_deg, 360_deg};
    WrappedFloat wrappedEqual{0_deg, 0_deg, 360_deg};

    EXPECT_TRUE(wrapped == wrappedEqual);
}

TEST(plusEquals, wrappedFloat)
{
    TappedFloat tapped{0, 0, 360};
    WrappedFloat wrapped{0_deg, 0_deg, 360_deg};

    tapped += tapped;

    wrapped += wrapped;

    EXPECT_EQ(tapped, WrappedFloat{wrapped});
}