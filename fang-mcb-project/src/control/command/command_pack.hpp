#pragma once

#include "tap/control/command_mapper.hpp"
#include "tap/control/command_mapping.hpp"

#include <span>

namespace fang::command
{
    /**
     * This is a family of classes which wire commands and subsystems together.
     * 
     * Mappers will often accept references to subsystems and then pass them into
     * the constructors of commands and whatnot.
     * 
     * They will also connect mappers as well.
     */
    class CommandPack
    {
    public:
        using CommandMapper = tap::control::CommandMapper;
        using CommandMapping = tap::control::CommandMapping;
        using RemoteState = tap::control::RemoteMapState;

        virtual void initialize() = 0;

        CommandPack(CommandMapper& mapper);
    protected:
        void registerCommandMappings(std::span<CommandMapping> mappings);
    private:
        tap::control::CommandMapper& mapper_;
    };
}