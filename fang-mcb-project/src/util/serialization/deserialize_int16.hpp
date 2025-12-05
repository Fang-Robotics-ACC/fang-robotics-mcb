#pragma once
#include "communication/uart/byte.hpp"
#include <cstdint>
namespace fang::serialization
{
inline uint16_t deserializeInt16(communication::Byte mostSignificant, communication::Byte leastSignificant)
{
    const uint16_t kCombined
    {
          (uint16_t) mostSignificant << 8
        | (uint16_t) leastSignificant << 0
    };

    return kCombined;
}
}