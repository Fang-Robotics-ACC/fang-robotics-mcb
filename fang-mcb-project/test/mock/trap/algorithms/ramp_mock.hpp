#ifndef FANG_ROBOTICS_MCB_TEST_MOCK_TRAP_ALGORITHMS_RAMP_MOCK_HPP
#define FANG_ROBOTICS_MCB_TEST_MOCK_TRAP_ALGORITHMS_RAMP_MOCK_HPP
#include "wrap/trap/algorithms/ramp.hpp"

#include <gmock/gmock.h>

namespace trap::algorithms
{
    template<typename ValueUnit, typename TimeUnit>
    class RampMock : public Ramp<ValueUnit, TimeUnit>
    {
    public:
        MOCK_METHOD(void, setTarget, (ValueUnit target), (override));
        MOCK_METHOD(ValueUnit, getTarget(), (const, override));
        MOCK_METHOD(void, setSpeed, (double speed), (override));
        MOCK_METHOD(void, update, (), (override));
        MOCK_METHOD(ValueUnit, getValue, (), (const, override));
        MOCK_METHOD(bool, isTargetReached, (), (const, override));
    };
}
#endif