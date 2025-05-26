#ifndef FANG_ROBOTICS_MCB_ROBOT_HPP
#define FANG_ROBOTICS_MCB_ROBOT_HPP
#include "robot_type.hpp"
namespace control
{
    #if defined(TARGET_INFANTRY_PIERCE)
    #include "pierce.hpp"
    using Robot = Pierce;
    #endif
}
#endif