#include <array>
#include "i_bus.hpp"

namespace fang::communication::ibus
{
    /**
     * This
     */
    class Packet : public std::array<Byte, kPacketSize>
    {
    };
}