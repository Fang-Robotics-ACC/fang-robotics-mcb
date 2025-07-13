#ifndef FANG_ROBOTICS_MCB_ROBOT_HPP
#define FANG_ROBOTICS_MCB_ROBOT_HPP
#include "robot_type.hpp"
#if defined(TARGET_INFANTRY_PIERCE)
#include "robot/variant/pierce/pierce_config.hpp"
#include "robot/variant/pierce/pierce.hpp"
using Robot = control::Pierce;
static const Robot::Config k_robotConfig{control::k_pierceConfig};
#endif
#endif