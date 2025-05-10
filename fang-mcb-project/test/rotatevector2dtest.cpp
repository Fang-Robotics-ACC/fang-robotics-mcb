#include "gtest/gtest.h"
#include "rotatevector2d.hpp"

#include "unitaliases.hpp"
#include "mathaliases.hpp"

#include <cmath>

//The general error is 6e-15, which is 15 decimal places. This is inconsequential for the application
//Counterrotation error is around 1e-10
const double k_tolerance{1e-10};

TEST(RotateVector2D, counterClockwise)
{
    {
    mathAliases::AbstractVector2D testVector{0.0, 1.0};
    //Rotate the unit vector
    mathAliases::AbstractVector2D expectedVector{-std::cos(Radians{Degrees{45}}.to<double>()), std::cos(Radians{Degrees{45}}.to<double>())};
    Degrees rotation{45};

    mathAliases::AbstractVector2D outputVector{util::math::rotateVector2D(testVector, rotation)};

    EXPECT_NEAR(outputVector.x, expectedVector.x, k_tolerance);
    EXPECT_NEAR(outputVector.y, expectedVector.y, k_tolerance);
    }

    {
    mathAliases::AbstractVector2D testVector{0.0, 100.0};
    mathAliases::AbstractVector2D expectedVector{-100.0, 0.0};
    Degrees rotation{90};

    mathAliases::AbstractVector2D outputVector{util::math::rotateVector2D(testVector, rotation)};

    EXPECT_NEAR(outputVector.x, expectedVector.x, k_tolerance);
    EXPECT_NEAR(outputVector.y, expectedVector.y, k_tolerance);
    }
}

TEST(RotateVector2D, clockwise)
{
    {
    mathAliases::AbstractVector2D testVector{0.0, 1.0};
    //Rotate the unit vector
    mathAliases::AbstractVector2D expectedVector{std::cos(Radians{Degrees{45}}.to<double>()), std::cos(Radians{Degrees{45}}.to<double>())};
    Degrees rotation{-45};

    mathAliases::AbstractVector2D outputVector{util::math::rotateVector2D(testVector, rotation)};

    EXPECT_NEAR(outputVector.x, expectedVector.x, k_tolerance);
    EXPECT_NEAR(outputVector.y, expectedVector.y, k_tolerance);
    }

    {
    mathAliases::AbstractVector2D testVector{0.0, 100.0};
    mathAliases::AbstractVector2D expectedVector{100.0, 0.0};
    Degrees rotation{-90};

    mathAliases::AbstractVector2D outputVector{util::math::rotateVector2D(testVector, rotation)};

    EXPECT_NEAR(outputVector.x, expectedVector.x, k_tolerance);
    EXPECT_NEAR(outputVector.y, expectedVector.y, k_tolerance);
    }
}

TEST(RotateVector2D, zero)
{
    {
    mathAliases::AbstractVector2D testVector{0.0, 1.0};
    //Rotate the unit vector
    mathAliases::AbstractVector2D expectedVector{testVector};
    Degrees rotation{0};

    mathAliases::AbstractVector2D outputVector{util::math::rotateVector2D(testVector, rotation)};

    EXPECT_NEAR(outputVector.x, expectedVector.x, k_tolerance);
    EXPECT_NEAR(outputVector.y, expectedVector.y, k_tolerance);
    }

    {
    mathAliases::AbstractVector2D testVector{234.2, -169589.0};
    //Rotate the unit vector
    mathAliases::AbstractVector2D expectedVector{testVector};
    Degrees rotation{0};

    mathAliases::AbstractVector2D outputVector{util::math::rotateVector2D(testVector, rotation)};

    EXPECT_NEAR(outputVector.x, expectedVector.x, k_tolerance);
    EXPECT_NEAR(outputVector.y, expectedVector.y, k_tolerance);
    }
}

TEST(counterRotation, rotateVector2DTest)
{
    {
    mathAliases::AbstractVector2D testVector{0.0, 1.0};
    //Rotate the unit vector
    mathAliases::AbstractVector2D expectedVector{testVector};
    Degrees rotation{10};

    mathAliases::AbstractVector2D rotated{util::math::rotateVector2D(testVector, rotation)};
    mathAliases::AbstractVector2D outputVector{util::math::rotateVector2D(rotated, -rotation)};

    EXPECT_NEAR(outputVector.x, expectedVector.x, k_tolerance);
    EXPECT_NEAR(outputVector.y, expectedVector.y, k_tolerance);
    }

    {
    mathAliases::AbstractVector2D testVector{234.2, -169589.0};
    //Rotate the unit vector
    mathAliases::AbstractVector2D expectedVector{testVector};
    Degrees rotation{-100};

    mathAliases::AbstractVector2D rotated{util::math::rotateVector2D(testVector, rotation)};
    mathAliases::AbstractVector2D outputVector{util::math::rotateVector2D(rotated, -rotation)};

    EXPECT_NEAR(outputVector.x, expectedVector.x, k_tolerance);
    EXPECT_NEAR(outputVector.y, expectedVector.y, k_tolerance);
    }
}