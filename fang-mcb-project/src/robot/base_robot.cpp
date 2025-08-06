#include "base_robot.hpp"

namespace fang::robot
{
    BaseRobot::BaseRobot(Drivers& drivers, Subsystems&& subsystems, CommandPacks&& commandPacks):
        drivers_{drivers},
        subsystems_{subsystems},
        commandPacks_{commandPacks}
    {}

    /**
     * This will make it a lot easier to utilize maker functions
     */
    BaseRobot::BaseRobot(BaseRobot&& baseRobot):
        subsystems_{std::move(baseRobot.subsystems_)},
        commandPacks_{std::move(baseRobot.commandPacks_)}
    {}
}