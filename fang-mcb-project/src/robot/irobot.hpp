#pragma once

#include "wrap/rail/system/isystem.hpp"

namespace fang::robot
{
    /**
     * All robots should initialize and update :P
     */
    class IRobot : virtual public system::ISystem
    {
        virtual ~IRobot() {};
    };
}