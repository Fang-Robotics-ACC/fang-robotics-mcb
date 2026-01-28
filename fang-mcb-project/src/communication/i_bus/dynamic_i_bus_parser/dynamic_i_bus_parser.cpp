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
    FANG_ASSERT(bytes.size() == (kChannelSectionSize + kChecksumSectionSize), "Segment must be proper size.");
    // Begin by extracting the channel data and checksum
    ChannelSection channelSection_{coolSerial::Bytes{bytes.begin(), bytes.begin() + kChannelSectionSize}};

    // Extract checksum
    const std::array<coolSerial::Byte, 2>  kChecksumSection{};
    std::copy(bytes.end() - 2, bytes.end() - 1, kChecksumSection.begin());
    // Dangerous but the assertion checks asserts appropriate bounds
    const int kMaxIndex{kChannelSectionSize + kChecksumSectionSize - 1};
    // Least endian order
    const int kChecksumLeastSignificantByteIndex{kMaxIndex - 1};
    const int kChecksumMostSignficantByteIndex{kMaxIndex};
    const uint16_t checksum{serialization::deserializeUInt16(bytes[kChecksumMostSignficantByteIndex], bytes[kChecksumLeastSignificantByteIndex])};

    state_ = startOfFrameSearch_;
}
}