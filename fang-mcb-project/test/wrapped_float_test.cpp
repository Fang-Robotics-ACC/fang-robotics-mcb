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

TEST(minDifference, wrappedFloat)
{
    float value1{189};
    float value2{187};
    TappedFloat tapped1{value1, 0, 360};
    TappedFloat tapped2{value2, 0, 360};
    WrappedFloat wrapped1{Degrees{value1}, 0_deg, 360_deg};
    WrappedFloat wrapped2{Degrees{value2}, 0_deg, 360_deg};

    float tapDiff{tapped1.minDifference(tapped2)};
    EXPECT_LT(tapDiff, 0);
    Degrees wrappedDiff{wrapped1.minDifference(wrapped2)};

    EXPECT_DOUBLE_EQ(tapDiff, wrappedDiff.to<double>());
}

TEST(minDifferenceRaw, wrappedFloat)
{
    float value1{189};
    float value2{187};
    TappedFloat tapped1{value1, 0, 360};
    TappedFloat tapped2{value2, 0, 360};
    WrappedFloat wrapped1{Degrees{value1}, 0_deg, 360_deg};
    WrappedFloat wrapped2{Degrees{value2}, 0_deg, 360_deg};

    float tapDiff{tapped1.minDifference(value2)};
    Degrees wrappedDiff{wrapped1.minDifference(Degrees{value2})};

    EXPECT_DOUBLE_EQ(tapDiff, wrappedDiff.to<double>());
}

TEST(shiftBounds, wrappedFloat)
{
    float value{189};
    float shift{187};
    TappedFloat tapped{value, 0, 360};
    WrappedFloat wrapped{Degrees{value}, 0_deg, 360_deg};

    tapped.shiftBounds(shift);
    wrapped.shiftBounds(Degrees{shift});

    EXPECT_EQ(wrapped, WrappedFloat{tapped});

}

TEST(limitValue, wrappedFloat)
{
    float value1{3450};
    float value2{187};
    float value3{340};
    TappedFloat tapped1{value1, 0, 360};
    TappedFloat tapped2{value2, 0, 360};
    TappedFloat tapped3{value3, 0, 360};
    WrappedFloat wrapped1{Degrees{value1}, 0_deg, 360_deg};
    WrappedFloat wrapped2{Degrees{value2}, 0_deg, 360_deg};
    WrappedFloat wrapped3{Degrees{value3}, 0_deg, 360_deg};

    int tapStatus{0};
    int trapStatus{0};

    double resultTap{TappedFloat::limitValue(tapped1, tapped2, tapped3, &tapStatus)};
    Degrees resultWrap{WrappedFloat::limitValue(wrapped1, wrapped2, wrapped3, &trapStatus)};

    EXPECT_EQ(tapStatus, trapStatus);
    EXPECT_DOUBLE_EQ(resultTap, resultWrap.to<double>());
}

TEST(rangeOverlap, wrappedFloat)
{
    float value1{3450};
    float value2{187};
    float value3{340};
    float value4{340};
    TappedFloat tapped1{value1, 0, 360};
    TappedFloat tapped2{value2, 0, 360};
    TappedFloat tapped3{value3, 0, 360};
    TappedFloat tapped4{value4, 0, 360};
    WrappedFloat wrapped1{Degrees{value1}, 0_deg, 360_deg};
    WrappedFloat wrapped2{Degrees{value2}, 0_deg, 360_deg};
    WrappedFloat wrapped3{Degrees{value3}, 0_deg, 360_deg};
    WrappedFloat wrapped4{Degrees{value4}, 0_deg, 360_deg};



    const float resultTap{TappedFloat::rangeOverlap(tapped1, tapped2, tapped3, tapped4)};
    Degrees resultWrap{WrappedFloat::rangeOverlap(wrapped1, wrapped2, wrapped3, wrapped4)};

    EXPECT_DOUBLE_EQ(resultTap, resultWrap.to<double>());
}

TEST(setterGetterUnwrapped, wrappedFloat)
{
    float value{189};
    float newValue{370};
    TappedFloat tapped{value, 0, 360};
    WrappedFloat wrapped{Degrees{value}, 0_deg, 360_deg};


    tapped.setUnwrappedValue(newValue);
    wrapped.setUnwrappedValue(Degrees{newValue});

    TappedFloat expectedTapped{newValue, 0, 360};
    WrappedFloat expectedWrapped{Degrees{newValue}, 0_deg, 360_deg};

    EXPECT_EQ(tapped, expectedTapped);
    EXPECT_EQ(wrapped, expectedWrapped);

    EXPECT_EQ(wrapped, WrappedFloat{tapped});
}

TEST(setterGetterWrapped, wrappedFloat)
{
    float value{189};
    float newValue{370};
    TappedFloat tapped{value, 0, 360};
    WrappedFloat wrapped{Degrees{value}, 0_deg, 360_deg};


    tapped.setWrappedValue(newValue);
    wrapped.setWrappedValue(Degrees{newValue});

    TappedFloat expectedTapped{newValue, 0, 360};
    WrappedFloat expectedWrapped{Degrees{newValue}, 0_deg, 360_deg};

    EXPECT_EQ(tapped, expectedTapped);
    EXPECT_EQ(wrapped, expectedWrapped);

    EXPECT_EQ(wrapped, WrappedFloat{tapped});
}

TEST(normalizedGetter, wrappedFloat)
{
    float value{189};
    TappedFloat tapped{value, 0, 360};
    WrappedFloat wrapped{Degrees{value}, 0_deg, 360_deg};

    EXPECT_EQ(wrapped.getNormalized(), WrappedFloat{tapped.getNormalized()});
}

TEST(revolutionsGetter, wrappedFloat)
{
    float value{3089};
    TappedFloat tapped{value, 0, 360};
    WrappedFloat wrapped{Degrees{value}, 0_deg, 360_deg};

    EXPECT_EQ(wrapped.getRevolutions(), tapped.getRevolutions());
}

TEST(lowerBoundGetter, wrappedFloat)
{
    float value{3089};
    TappedFloat tapped{value, 0, 360};
    WrappedFloat wrapped{Degrees{value}, 0_deg, 360_deg};

    EXPECT_DOUBLE_EQ(wrapped.getLowerBound().to<double>(), tapped.getLowerBound());
}

TEST(upperBoundGetter, wrappedFloat)
{
    float value{3089};
    TappedFloat tapped{value, 0, 360};
    WrappedFloat wrapped{Degrees{value}, 0_deg, 360_deg};

    EXPECT_DOUBLE_EQ(wrapped.getUpperBound().to<double>(), tapped.getUpperBound());
}

