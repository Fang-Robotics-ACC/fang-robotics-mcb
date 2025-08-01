#ifndef FANG_ROBOTICS_MCB_TEST_MOCK_TRAP_ALGORITHMS_RAMP_2D_MOCK_HPP
#define FANG_ROBOTICS_MCB_TEST_MOCK_TRAP_ALGORITHMS_RAMP_2D_MOCK_HPP

#include "wrap/trap/algorithms/ramp_2d.hpp"
#include <gmock/gmock.h>

namespace trap::algorithms
{
    template<typename ValueUnit, typename TimeUnit>
    class Ramp2DMock : public Ramp2D<ValueUnit, TimeUnit>
    {
    public:
        using Vector2D = fang::math::Vector2D<ValueUnit>;

        MOCK_METHOD(void, setTarget, (const Vector2D& target), (override));
        MOCK_METHOD(Vector2D, getTarget, (), (const, override));
        MOCK_METHOD(void, setSpeed, (double speed), (override));
        MOCK_METHOD(Vector2D, getValue, (), (const, override));
        MOCK_METHOD(bool, isTargetReached, (), (const, override));
        MOCK_METHOD(void, update, (), (override));
    };
}
#endif