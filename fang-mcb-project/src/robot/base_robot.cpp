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
        drivers_ {baseRobot.drivers_},
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
            drivers_.commandScheduler.registerSubsystem(subsystem.get());
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