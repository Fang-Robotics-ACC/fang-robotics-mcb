#pragma once
#include "system/assert/fang_assert.hpp"
#include "util/serialization/deserialize_uint16.hpp"
#include "dynamic_i_bus_parser.hpp"
#include "communication/i_bus/i_bus_channel_section.hpp"

namespace fang::communication::ibus
{
DynamicParser::DynamicParser(coolSerial::ByteQueue& byteBuffer, ChannelDataFoundListener& channelDataFoundListener):
    channelDataFoundListener_{channelDataFoundListener},
    startOfFrameSearch_{byteBuffer, *this},
    segmentExtract_{byteBuffer, *this, kChannelSectionSize + kChannelSectionSize}
{}

void DynamicParser::startOfFrameFound()
{
    state_ = segmentExtract_;
}

void DynamicParser::segmentFound(const coolSerial::Bytes& bytes)
{
    // Begin by extracting the channel data and checksum
    ChannelSection channelSection{coolSerial::Bytes{bytes.begin(), bytes.begin() + kChannelSectionSize}};

    const uint16_t checksum{extractChecksumFromCombinedSegment(bytes)};

    if(channelSection.isValid(checksum))
    {
        channelDataFoundListener_.channelDataFound(channelSection.getChannelData());
    }
    state_ = startOfFrameSearch_;

}

uint16_t DynamicParser::extractChecksumFromCombinedSegment(const coolSerial::Bytes& bytes)
{
    FANG_ASSERT(bytes.size() == (kChannelSectionSize + kChecksumSectionSize), "Segment must be proper size.");

    const int kMaxIndex{kChannelSectionSize + kChecksumSectionSize - 1};
    // Least endian order
    const int kChecksumLeastSignificantByteIndex{kMaxIndex - 1};
    const int kChecksumMostSignficantByteIndex{kMaxIndex};

    // Dangerous but the assertion checks asserts appropriate bounds
    const uint16_t checksum{serialization::deserializeUInt16(bytes[kChecksumMostSignficantByteIndex], bytes[kChecksumLeastSignificantByteIndex])};

}
}