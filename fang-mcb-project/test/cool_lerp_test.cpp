#include "util/math/cool_lerp.hpp"

#include <gmock/gmock.h>

using Vector2D = math::CoolLerp::Vector2D;
TEST(zeroTest, coolLerp)
{
    const Vector2D dataPoint1{0.0, 0.0};
    const Vector2D dataPoint2{1.0, 1.0};
    math::CoolLerp lerp{dataPoint1, dataPoint2};
    EXPECT_DOUBLE_EQ(lerp.interpolate(0.0), 0.0);
}

TEST(linearInBound, coolLerp)
{
    const Vector2D dataPoint1{0.0, 0.0};
    const Vector2D dataPoint2{1.0, 1.0};
    math::CoolLerp lerp{dataPoint1, dataPoint2};
    EXPECT_DOUBLE_EQ(lerp.interpolate(0.5), 0.5);
    EXPECT_DOUBLE_EQ(lerp.interpolate(1.0), 1.0);
}

TEST(linearOutOfBound, coolLerp)
{
    const Vector2D dataPoint1{0.0, 0.0};
    const Vector2D dataPoint2{1.0, 1.0};
    math::CoolLerp lerp{dataPoint1, dataPoint2};
    EXPECT_DOUBLE_EQ(lerp.interpolate(-27.0), -27.0);
    EXPECT_DOUBLE_EQ(lerp.interpolate(24.0), 24.0);
    EXPECT_DOUBLE_EQ(lerp.interpolate(27.0), 27.0);
}