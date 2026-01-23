#pragma once

#include <cstdint>

namespace fang::serialize
{
struct uint16Bytes
{
    uint8_t mostSignificant;
    uint8_t leastSignificant;
};
}