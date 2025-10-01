#include "communication/cool_protocol/janky_float.hpp"
#include <gtest/gtest.h>

namespace fang::communication::jankyFloatTest
{
    TEST(JankyFloat, matchTest)
    {
        const float kTest{345345};
        const coolSerial::Bytes kSerialized{JankyFloat::serialize(kTest)};
        const float kRecovered{JankyFloat::deserialize(kSerialized)};
        // The recovery should be exact
        EXPECT_EQ(kTest, kRecovered);
    }
}