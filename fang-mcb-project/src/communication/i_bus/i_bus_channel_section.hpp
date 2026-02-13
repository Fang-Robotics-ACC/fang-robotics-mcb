#include "i_bus.hpp"
#include "i_bus_channel_data.hpp"
#include "cool_serial/bytes.hpp"

#include <array>
namespace fang::communication::ibus
{
/**
 * This stores the bytes of the channel section. It is capable of deserializing
 * the bytes into 
 */
class ChannelSection
{
public:
    using ChannelBytes = std::array<Byte, kChannelSectionSize>;

    ChannelSection(const ChannelBytes& bytes);

    /**
     * Adapter for bytes
     */
    ChannelSection(const coolSerial::Bytes& bytes);
    ChannelData getChannelData() const;

    /**
     * The IBus checksum is calculated by summing all of the bytes and subtracting them from 
     * 0xFFFF
     * https://blog.dsp.id.au/posts/2017/10/22/flysky-ibus-protocol/
     */
    uint16_t calculateChecksum() const;

    /**
     * You can feed a checksum from the checksum section to verify
     */
    bool isValid(uint16_t checkSum) const;
private:
    // Not constant but all other functions are const
    // Not constant to avoid unnecessary double copies
    std::array<Byte, kChannelSectionSize> bytes_;
};
}