#include "i_bus.hpp"

#include <array>
#include <cstdint>

namespace fang::communication::ibus
{
    using ChannelData  = std::array<std::uint16_t, kChannelCount>;
}
