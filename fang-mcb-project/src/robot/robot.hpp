#ifndef FANG_ROBOTICS_MCB_ROBOT_HPP
#define FANG_ROBOTICS_MCB_ROBOT_HPP
#if defined(TARGET_INFANTRY_PIERCE)
#include "robot/variant/pierce/pierce_config.hpp"
#include "robot/variant/pierce/pierce.hpp"
using Robot = fang::robot::Pierce;
static const Robot::Config& k_robotConfig{fang::robot::k_pierceConfig};

// #include "robot/variant/pierce_auto_test/pierce_auto_test.hpp"
// #include "robot/variant/pierce_auto_test/pierce_auto_test_config.hpp"
// using Robot = fang::robot::PierceAutoTest;
// static const Robot::Config& k_robotConfig{fang::robot::k_pierceAutoTestConfig};

#endif

#if defined(TARGET_PIERCE_AUTO_TEST)
#include "robot/variant/pierce_auto_test/pierce_auto_test.hpp"
#include "robot/variant/pierce_auto_test/pierce_auto_test_config.hpp"
using Robot = fang::robot::PierceAutoTest;
static const Robot::Config& k_robotConfig{fang::robot::k_pierceAutoTestConfig};

#endif
#endif