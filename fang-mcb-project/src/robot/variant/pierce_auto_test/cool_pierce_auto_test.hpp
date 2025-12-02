#pragma once
#include "pierce_auto_test_config.hpp"
#include "pierce_auto_test.hpp"

namespace fang::robot
{

    /**
     * This automatically constructs the default robot
     */
    class CoolPierceAutoTest : public PierceAutoTest
    {
    public:
        CoolPierceAutoTest(Drivers& drivers):
            PierceAutoTest{drivers, getPierceAutoTestConfig()}
        {
        }
    };
}