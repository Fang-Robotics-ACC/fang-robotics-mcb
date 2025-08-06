#pragma once

#include "irobot.hpp"

#include "driver/drivers.hpp"
#include "control/command/command_pack.hpp"

#include "tap/control/subsystem.hpp"
#include "tap/control/command_scheduler.hpp"

#include <memory>

namespace fang::robot
{
    /**
     * All a robot does is manage subsystems and commands
     * + extra specific stuff too sometimes
     */
    class BaseRobot : public IRobot
    {
    public:
        // Even though inheritors need to use maker functions, the benefits
        // of testability and ownership are worth it
        using Subsystems = std::vector<std::unique_ptr<tap::control::Subsystem>>;
        using CommandPacks = std::vector<std::unique_ptr<command::CommandPack>>;

        /**
         * The base robot will take ownership of the information
         */
        BaseRobot
        (
            tap::control::CommandScheduler& commandScheduler,
            Subsystems&& subsystems,
            CommandPacks&& commandPacks
        );

        /**
         * This will make it a lot easier to utilize maker functions
         */
        BaseRobot(BaseRobot&& baseRobot);

        virtual void initialize() override;

        /// Not virtual so that it can be passed around in maker functions
        virtual void update() {};
    protected:
        void registerSubsystems();
        void initializeSubsystems();
        void initializeCommandPacks();
    private:
        tap::control::CommandScheduler& commandScheduler_;
        Subsystems subsystems_;
        CommandPacks commandPacks_;
    };
}