#include "i_bus.hpp"

#include <array>
#include <cstdint>

namespace fang::communication
{
    class IBusChannelData : public std::array<std::uint16_t, IBus::kChannelCount>
    {
    };
}
