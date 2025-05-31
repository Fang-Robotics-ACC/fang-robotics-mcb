#ifndef FANG_ROBOTICS_MCB_MATH_COOL_LERP_HPP
#define FANG_ROBOTICS_MCB_MATH_COOL_LERP_HPP
#include "vector2d.hpp"
namespace math
{
    /**
     * This interpolates arbitrary values between two datapoints
     * x is input, y is the output for that given input
     * 
     * This is not as convoluted as modm's lerp but it's more capable than std::lerp
     * Hence, it is the coolest lerp :D
     */
    class CoolLerp
    {
    public:
        using Vector2D = data::math::Vector2D<double>;
        /**
         * x corresponds to the intput
         * y corresponds to the output
         * dataPoint1 should have the lesser input value
         * The datapoints should have different input values to have a defined
         * slope.
         */
        CoolLerp(const Vector2D& dataPoint1, const Vector2D& dataPoint2);

        double interpolate(double input) const;
    private:
        const Vector2D mk_dataPoint1;
        const Vector2D mk_dataPoint2;
        const double mk_input_range;
    };
}
#endif