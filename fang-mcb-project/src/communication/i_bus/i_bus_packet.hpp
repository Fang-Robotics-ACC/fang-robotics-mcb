#include <array>
#include "i_bus.hpp"

namespace fang::communication
{
    /**
     * This
     */
    class IBusPacket : public std::array<Byte, IBus::kPacketSize>
    {
    };
}