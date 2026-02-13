#pragma once

#include <cstdint>

namespace fang::serialize
{
struct UInt16Bytes
{
    uint8_t mostSignificant;
    uint8_t leastSignificant;
};

UInt16Bytes serializeUInt16(uint16_t integer)
{
    uint8_t mostSignificantByte{integer >> 0 & (0xff)};
    uint8_t leastSignificantByte{integer >> 8 & (0xff)};

    return 
    {
        .mostSignificant = mostSignificantByte,
        .leastSignificant = leastSignificantByte
    };
}
}