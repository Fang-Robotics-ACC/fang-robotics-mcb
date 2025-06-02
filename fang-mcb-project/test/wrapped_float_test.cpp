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
//WrappedFloat is a unit based wrapped for the tapproot version
//These test if the operation values are the same
TEST(equalOperator, wrappedFloat)
{
    WrappedFloat wrapped{0_deg, 0_deg, 360_deg};
    WrappedFloat wrappedEqual{0_deg, 0_deg, 360_deg};

    EXPECT_TRUE(wrapped == wrappedEqual);
}

TEST(plusEquals, wrappedFloat)
{
    float value1{189};
    float value2{187};
    TappedFloat tapped1{value1, 0, 360};
    TappedFloat tapped2{value2, 0, 360};
    WrappedFloat wrapped1{Degrees{value1}, 0_deg, 360_deg};
    WrappedFloat wrapped2{Degrees{value2}, 0_deg, 360_deg};

    tapped1 += tapped2;
    wrapped1 += wrapped2;

    EXPECT_EQ(wrapped1, WrappedFloat{tapped1});
}

TEST(minusEquals, wrappedFloat)
{
    float value1{189};
    float value2{187};
    TappedFloat tapped1{value1, 0, 360};
    TappedFloat tapped2{value2, 0, 360};
    WrappedFloat wrapped1{Degrees{value1}, 0_deg, 360_deg};
    WrappedFloat wrapped2{Degrees{value2}, 0_deg, 360_deg};

    tapped1 -= tapped2;
    wrapped1 -= wrapped2;

    EXPECT_EQ(wrapped1, WrappedFloat{tapped1});
}

TEST(plus, wrappedFloat)
{
    float value1{189};
    float value2{187};
    TappedFloat tapped1{value1, 0, 360};
    TappedFloat tapped2{value2, 0, 360};
    WrappedFloat wrapped1{Degrees{value1}, 0_deg, 360_deg};
    WrappedFloat wrapped2{Degrees{value2}, 0_deg, 360_deg};

    TappedFloat tapped{tapped1 + tapped2};
    WrappedFloat wrapped{wrapped1 + wrapped2};

    EXPECT_EQ(wrapped, WrappedFloat{tapped});
}

TEST(minus, wrappedFloat)
{
    float value1{189};
    float value2{187};
    TappedFloat tapped1{value1, 0, 360};
    TappedFloat tapped2{value2, 0, 360};
    WrappedFloat wrapped1{Degrees{value1}, 0_deg, 360_deg};
    WrappedFloat wrapped2{Degrees{value2}, 0_deg, 360_deg};

    TappedFloat tapped{tapped1 - tapped2};
    WrappedFloat wrapped{wrapped1 - wrapped2};

    EXPECT_EQ(wrapped, WrappedFloat{tapped});
}