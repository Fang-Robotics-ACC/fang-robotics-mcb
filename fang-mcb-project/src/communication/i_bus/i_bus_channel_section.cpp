#include "i_bus_channel_section.hpp"
#include "util/serialization/deserialize_uint16.hpp"
namespace fang::communication
{
IBusChannelSection::IBusChannelSection(const ChannelBytes& bytes) : bytes_{bytes}
{
}

IBusChannelData IBusChannelSection::getChannelData() const
    {
        IBusChannelData channelData{};
        // There are two bytes per 16 bit int
        // msb is the first int
        for(int channel{0}; channel < IBus::kChannelCount; ++channel )
        {
            const int index{channel * 2};
            // They are sent in reverse
            const Byte kMostSignificantByte{bytes_.at(index + 1)};
            const Byte kLestSignificantByte{bytes_.at(index)};

            channelData.at(channel) = serialization::deserializeUInt16(kMostSignificantByte, kLestSignificantByte);
        }

        return channelData; 
    }

    /**
     * The IBus checksum is calculated by summing all of the bytes and subtracting them from 
     * 0xFFFF
     * https://blog.dsp.id.au/posts/2017/10/22/flysky-ibus-protocol/
     */
    uint16_t IBusChannelSection::calculateChecksum() const
    {
        uint16_t byteSum{0};

        for(const Byte& byte : bytes_)
        {
            byteSum += byte;
        }

        // For some reason the actual checksum is the sum subtracted from a constant :P
        return IBus::kChecksumConstant - byteSum;
    }

    /**
     * You can feed a checksum from the checksum section to verify
     */
    bool IBusChannelSection::isValid(uint16_t checkSum) const
    {
        return checkSum == calculateChecksum();
    }
}