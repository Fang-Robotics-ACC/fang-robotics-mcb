#ifndef FANG_ROBOTICS_MCB_ROBOT_HPP
#define FANG_ROBOTICS_MCB_ROBOT_HPP
#include "robot_type.hpp"
#if defined(TARGET_INFANTRY_PIERCE)
#include "robots/pierce/pierce_config.hpp"
#include "robots/pierce/pierce.hpp"
using Robot = control::Pierce;
static const Robot::Config k_robotConfig{control::k_pierceConfig};
#endif
#endif