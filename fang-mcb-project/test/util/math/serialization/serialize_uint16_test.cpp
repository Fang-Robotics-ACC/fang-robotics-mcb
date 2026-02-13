#include "util/serialization/serialize_uint16.hpp"

#include <gtest/gtest.h>

namespace fang::serialize::SerializeUint16Test
{
TEST(SerialzeUInt16, basicMatch)
{
    constexpr uint8_t mostSignificant{0xab};
    constexpr uint8_t leastSignificant{0xcd};

    constexpr uint16_t integer
    {
        (uint16_t) leastSignificant << 8 |
        (uint16_t) mostSignificant << 0
    };

    UInt16Bytes bytes{serializeUInt16(integer)};
    EXPECT_EQ(bytes.leastSignificant, leastSignificant);
    EXPECT_EQ(bytes.mostSignificant, mostSignificant);
}
}