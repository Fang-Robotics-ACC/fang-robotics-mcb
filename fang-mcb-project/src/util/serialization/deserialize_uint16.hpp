#pragma once
#include "communication/uart/byte.hpp"

#include <bit>
#include <cstdint>
namespace fang::serialization
{
inline uint16_t deserializeUInt16(communication::Byte mostSignificant, communication::Byte leastSignificant)
{
    const uint16_t kCombined
    {
          (uint16_t) mostSignificant << 8
        | (uint16_t) leastSignificant << 0
    };

    //const int16_t* integer {reinterpret_cast<const int16_t*>(&kCombined)};
    
    return kCombined;
}
}