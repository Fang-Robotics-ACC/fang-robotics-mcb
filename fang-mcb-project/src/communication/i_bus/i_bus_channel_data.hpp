#include "i_bus.hpp"

#include <array>

namespace fang::communication
{
    class IBusChannelData : public std::array<Byte, IBus::kChannelCount>
    {
    public:
    };
}
