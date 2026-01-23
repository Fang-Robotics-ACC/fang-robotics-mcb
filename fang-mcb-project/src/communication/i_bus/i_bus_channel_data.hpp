#include "i_bus.hpp"

#include <array>
#include <cstdint>

namespace fang::communication
{
    using IBusChannelData  = std::array<std::uint16_t, IBus::kChannelCount>;
}
