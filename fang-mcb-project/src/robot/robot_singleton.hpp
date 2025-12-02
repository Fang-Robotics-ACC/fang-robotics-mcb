#ifndef FANG_ROBOTICS_MCB_ROBOT_HPP
#define FANG_ROBOTICS_MCB_ROBOT_HPP
#include "irobot.hpp"
namespace fang
{
// TODO: Make into singleton with api like RobotSingleton::getRobot()
class RobotSingleton
{
public:
    static robot::IRobot& getRobot();

private:
    static robot::IRobot& robot;
};
}

#endif