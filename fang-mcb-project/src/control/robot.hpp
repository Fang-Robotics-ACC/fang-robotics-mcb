#ifndef FANG_ROBOTICS_MCB_ROBOT_HPP
#define FANG_ROBOTICS_MCB_ROBOT_HPP
namespace control
{
#if defined(TARGET_INFANTRY_PIERCE)
#include "infantry.hpp"
using Robot = Pierce;
#endif
}
#endif