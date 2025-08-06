#include "base_robot.hpp"

namespace fang::robot
{
    BaseRobot::BaseRobot
    (
        tap::control::CommandScheduler& commandScheduler,
        Subsystems&& subsystems,
        CommandPacks&& commandPacks
    ):
        commandScheduler_{commandScheduler},
        subsystems_{std::move(subsystems)},
        commandPacks_{std::move(commandPacks)}
    {}

    /**
     * This will make it a lot easier to utilize maker functions
     */
    BaseRobot::BaseRobot(BaseRobot&& baseRobot):
        commandScheduler_ {baseRobot.commandScheduler_},
        subsystems_{std::move(baseRobot.subsystems_)},
        commandPacks_{std::move(baseRobot.commandPacks_)}
    {}

    void BaseRobot::initialize()
    {
        initializeSubsystems();
        registerSubsystems();
        initializeCommandPacks();
    }

    void BaseRobot::initializeSubsystems()
    {
        for(auto& subsystem : subsystems_)
        {
            subsystem->initialize();
        }
    }

    void BaseRobot::registerSubsystems()
    {
        for(auto& subsystem : subsystems_)
        {
            // Must pass by raw pointer because taproot loves raw pointers
            // As of the last documentation this is a non-owning pointer :P
            commandScheduler_.registerSubsystem(subsystem.get());
        }
    }

    void BaseRobot::initializeCommandPacks()
    {
        for(auto& commandPack: commandPacks_)
        {
            commandPack->initialize();
        }
    }
}