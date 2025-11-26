#pragma once
#include "pierce_config.hpp"
#include "pierce.hpp"

namespace fang::robot
{
    /**
     * This automatically constructs the default robot
     */
    class CoolPierce : public Pierce
    {
    public:
        CoolPierce(Drivers& drivers):
            Pierce{drivers, getPierceConfig()}
        {
        }
    };
}