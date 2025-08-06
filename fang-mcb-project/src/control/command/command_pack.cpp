#include "command_pack.hpp"

namespace fang::command
{
    CommandPack::CommandPack(CommandMapper& mapper) : mapper_{mapper}
    {
    }

    void CommandPack::registerCommandMappings(std::span<std::reference_wrapper<CommandMapping>> mappings)
    {
        for(auto mapping : mappings) 
        {
            mapper_.addMap(&mapping.get());
        }
    }
}