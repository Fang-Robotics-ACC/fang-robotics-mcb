#include "gtest/gtest.h"
#include "util/math/geometry/rotate_vector_2d.hpp"

#include "unitaliases.hpp"
#include "util/math/linear/vector_alias.hpp"

#include <cmath>

//The general error is 6e-15, which is 15 decimal places. This is inconsequential for the application
//Counterrotation error is around 1e-10
const double k_tolerance{1e-10};

TEST(RotateVector2D, counterClockwise)
{
    {
    math::AbstractVector2D testVector{0.0, 1.0};
    //Rotate the unit vector
    math::AbstractVector2D expectedVector{-std::cos(Radians{Degrees{45}}.to<double>()), std::cos(Radians{Degrees{45}}.to<double>())};
    Degrees rotation{45};

    math::AbstractVector2D outputVector{math::rotateVector2D(testVector, rotation)};

    EXPECT_NEAR(outputVector.x, expectedVector.x, k_tolerance);
    EXPECT_NEAR(outputVector.y, expectedVector.y, k_tolerance);
    }

    {
    math::AbstractVector2D testVector{0.0, 100.0};
    math::AbstractVector2D expectedVector{-100.0, 0.0};
    Degrees rotation{90};

    math::AbstractVector2D outputVector{math::rotateVector2D(testVector, rotation)};

    EXPECT_NEAR(outputVector.x, expectedVector.x, k_tolerance);
    EXPECT_NEAR(outputVector.y, expectedVector.y, k_tolerance);
    }
}

TEST(RotateVector2D, clockwise)
{
    {
    math::AbstractVector2D testVector{0.0, 1.0};
    //Rotate the unit vector
    math::AbstractVector2D expectedVector{std::cos(Radians{Degrees{45}}.to<double>()), std::cos(Radians{Degrees{45}}.to<double>())};
    Degrees rotation{-45};

    math::AbstractVector2D outputVector{math::rotateVector2D(testVector, rotation)};

    EXPECT_NEAR(outputVector.x, expectedVector.x, k_tolerance);
    EXPECT_NEAR(outputVector.y, expectedVector.y, k_tolerance);
    }

    {
    math::AbstractVector2D testVector{0.0, 100.0};
    math::AbstractVector2D expectedVector{100.0, 0.0};
    Degrees rotation{-90};

    math::AbstractVector2D outputVector{math::rotateVector2D(testVector, rotation)};

    EXPECT_NEAR(outputVector.x, expectedVector.x, k_tolerance);
    EXPECT_NEAR(outputVector.y, expectedVector.y, k_tolerance);
    }
}

TEST(RotateVector2D, zero)
{
    {
    math::AbstractVector2D testVector{0.0, 1.0};
    //Rotate the unit vector
    math::AbstractVector2D expectedVector{testVector};
    Degrees rotation{0};

    math::AbstractVector2D outputVector{math::rotateVector2D(testVector, rotation)};

    EXPECT_NEAR(outputVector.x, expectedVector.x, k_tolerance);
    EXPECT_NEAR(outputVector.y, expectedVector.y, k_tolerance);
    }

    {
    math::AbstractVector2D testVector{234.2, -169589.0};
    //Rotate the unit vector
    math::AbstractVector2D expectedVector{testVector};
    Degrees rotation{0};

    math::AbstractVector2D outputVector{math::rotateVector2D(testVector, rotation)};

    EXPECT_NEAR(outputVector.x, expectedVector.x, k_tolerance);
    EXPECT_NEAR(outputVector.y, expectedVector.y, k_tolerance);
    }
}

TEST(counterRotation, rotateVector2DTest)
{
    {
    math::AbstractVector2D testVector{0.0, 1.0};
    //Rotate the unit vector
    math::AbstractVector2D expectedVector{testVector};
    Degrees rotation{10};

    math::AbstractVector2D rotated{math::rotateVector2D(testVector, rotation)};
    math::AbstractVector2D outputVector{math::rotateVector2D(rotated, -rotation)};

    EXPECT_NEAR(outputVector.x, expectedVector.x, k_tolerance);
    EXPECT_NEAR(outputVector.y, expectedVector.y, k_tolerance);
    }

    {
    math::AbstractVector2D testVector{234.2, -169589.0};
    //Rotate the unit vector
    math::AbstractVector2D expectedVector{testVector};
    Degrees rotation{-100};

    math::AbstractVector2D rotated{math::rotateVector2D(testVector, rotation)};
    math::AbstractVector2D outputVector{math::rotateVector2D(rotated, -rotation)};

    EXPECT_NEAR(outputVector.x, expectedVector.x, k_tolerance);
    EXPECT_NEAR(outputVector.y, expectedVector.y, k_tolerance);
    }
}