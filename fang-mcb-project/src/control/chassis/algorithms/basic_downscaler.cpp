#include "control/chassis/algorithms/basic_downscaler.hpp"

namespace control::chassis
{
    BasicDownscaler::BasicDownscaler(double downscaleCoefficient)
    :   m_downscaleCoefficient{downscaleCoefficient}
    {
    }

    double BasicDownscaler::basicDownscale(double speed, double coefficient)
    {
        //https://www.desmos.com/calculator/5xqaxqilmn
        //The function is designed so that no matter what k is, if the speed is zero
        //it returns a 1, i.e. full speed.
        const double numerator{coefficient};
        const double denominator{speed + coefficient};
        return  numerator / denominator;
    }

    double BasicDownscaler::getDownscale (const MetersPerSecond& speed)
    {
        return basicDownscale(static_cast<double>(speed), m_downscaleCoefficient);
    }
}