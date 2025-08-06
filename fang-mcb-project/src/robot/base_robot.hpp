#pragma once

#include "irobot.hpp"
#include "tap/control/subsystem.hpp"
#include "control/command/command_pack.hpp"

#include <memory>

namespace fang::robot
{
    /**
     * All a robot does is manage subsystems and commands
     * + extra specific stuff too sometimes
     */
    class BaseRobot
    {
    public:
        // Even though inheritors need to use maker functions, the benefits
        // of testability and ownership are worth it
        using Subsystems = std::vector<std::unique_ptr<tap::control::Subsystem>>;
        using CommandPacks = std::vector<std::unique_ptr<command::CommandPack>>;

        /**
         * The base robot will take ownership of the information
         */
        BaseRobot(Subsystems&& subsystems, CommandPacks&& commandPacks);

        /**
         * This will make it a lot easier to utilize maker functions
         */
        BaseRobot(BaseRobot&& baseRobot);
    private:
        Subsystems subsystems_;
        CommandPacks commandPacks_;
    };
}