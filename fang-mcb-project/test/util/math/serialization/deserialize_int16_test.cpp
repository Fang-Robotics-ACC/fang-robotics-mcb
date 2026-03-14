#include "util/serialization/deserialize_uint16.hpp"

#include <gtest/gtest.h>
#include <cstdint>

namespace fang::serialization::DeserializeInt16Test
{
using Byte = communication::Byte;
TEST(deserializeInt16, zero)
{
    // If all the bytes are zero, the corresponding number should be zero
    // Bytes for zero
    constexpr Byte kMostSignificant{0x0};
    constexpr Byte kLeastSignificant{0x0};
    constexpr uint16_t kExpected{0};

    const uint16_t kOutput{deserializeUInt16(kMostSignificant, kLeastSignificant)} ;

    EXPECT_EQ(kOutput, kExpected);
}

TEST(deserializeInt16, 256Test)
{
    // 0x01 | 0x00 = 0x0100, which is 256 in decimal
    // If all the bytes are zero, the corresponding number should be zero
    // Bytes for zero
    constexpr Byte kMostSignificant{0x01};
    constexpr Byte kLeastSignificant{0x00};
    constexpr uint16_t kExpected{256};

    const uint16_t kOutput{deserializeUInt16(kMostSignificant, kLeastSignificant)} ;

    EXPECT_EQ(kOutput, kExpected);

}
}