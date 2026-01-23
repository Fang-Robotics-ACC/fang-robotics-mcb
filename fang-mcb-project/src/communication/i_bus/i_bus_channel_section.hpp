#include "i_bus.hpp"
#include "i_bus_channel_data.hpp"
#include "util/serialization/deserialize_uint16.hpp"

#include <array>
namespace fang::communication
{
/**
 * This stores the bytes of the channel section. It is capable of deserializing
 * the bytes into 
 */
class IBusChannelSection : public std::array<Byte, IBus::kChannelSectionSize>
{
public:
    IBusChannelData getChannelData() const
    {
        IBusChannelData channelData{};
        // There are two bytes per 16 bit int
        // msb is the first int
        for(int channel{0}; channel < IBus::kChannelSectionSize; ++ channel)
        {
            // They are sent in reverse
            const Byte kMostSignificantByte{at(channel + 1)};
            const Byte kLestSignificantByte{at(channel)};

            channelData.at(channel) = serialization::deserializeUInt16(kMostSignificantByte, kLestSignificantByte);
        }
    }
};
}