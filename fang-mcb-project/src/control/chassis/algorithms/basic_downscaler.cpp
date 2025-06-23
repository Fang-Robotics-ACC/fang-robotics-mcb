#include "control/chassis/algorithms/basic_downscaler.hpp"

namespace control::chassis
{
    BasicDownscaler::BasicDownscaler(double downscaleCoefficient)
    :   m_downscaleCoefficient{downscaleCoefficient}
    {
    }
}