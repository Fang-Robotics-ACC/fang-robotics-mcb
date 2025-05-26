#ifndef FANG_ROBOTICS_MCB_ROBOT_HPP
#define FANG_ROBOTICS_MCB_ROBOT_HPP
namespace control
{
#if defined(TARGET_INFANTRY)
#include "infantry.hpp"
using Robot = Infantry;
#endif
}
#endif