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
class IBusChannelSection
{
public:
    using ChannelBytes = std::array<Byte, IBus::kChannelSectionSize>;

    IBusChannelSection(const ChannelBytes& bytes);
    IBusChannelData getChannelData() const;

    /**
     * The IBus checksum is calculated by summing all of the bytes and subtracting them from 
     * 0xFFFF
     * https://blog.dsp.id.au/posts/2017/10/22/flysky-ibus-protocol/
     */
    uint16_t calculateChecksum();

    /**
     * You can feed a checksum from the checksum section to verify
     */
    bool isValid(uint16_t checkSum);
private:
    std::array<Byte, IBus::kChannelSectionSize> bytes_;
};
}