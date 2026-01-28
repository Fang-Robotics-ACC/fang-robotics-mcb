#pragma once
#include "dynamic_i_bus_parser.hpp"

namespace fang::communication::ibus
{
    DynamicParser::DynamicParser(coolSerial::ByteQueue& byteBuffer):
        startOfFrameSearch_{byteBuffer, *this},
        segmentExtract_{byteBuffer, *this, kChannelSectionSize + kChannelSectionSize}
    {}

    void DynamicParser::startOfFrameFound()
    {
    }

    void DynamicParser::segmentFound(const coolSerial::Bytes& bytes)
    {
    }
}