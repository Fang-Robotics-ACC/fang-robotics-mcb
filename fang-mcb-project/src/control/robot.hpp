#ifndef FANG_ROBOTICS_MCB_ROBOT_HPP
#define FANG_ROBOTICS_MCB_ROBOT_HPP
#include "robot_type.hpp"
#if defined(TARGET_INFANTRY_PIERCE)
#include "control/robots/pierce/pierce.hpp"
using Robot = control::Pierce;
#endif
#endif