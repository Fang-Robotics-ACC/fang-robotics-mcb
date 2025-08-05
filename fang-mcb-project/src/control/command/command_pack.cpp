#include "command_pack.hpp"

namespace fang::command
{
    CommandPack::CommandPack(CommandMapper& mapper) : mapper_{mapper}
    {
    }
    void CommandPack::registerCommands(std::span<CommandMapping> mappings)
    {
        for(auto& mapping : mappings) 
        {
            mapper_.addMap(&mapping);
        }
    }
}