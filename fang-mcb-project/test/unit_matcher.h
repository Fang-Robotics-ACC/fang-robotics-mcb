#ifndef FANG_ROBOTICS_MCB_UNIT_MATCHER_HPP
#define FANG_ROBOTICS_MCB_UNIT_MATCHER_HPP
#include <gmock/gmock.h>

namespace testing
{
    MATCHER_P(UnitEq, expected, "")
    {
        return std::abs(static_cast<double>(arg) - static_cast<double>(expected)) <= 1e-10;
    }
}
#endif