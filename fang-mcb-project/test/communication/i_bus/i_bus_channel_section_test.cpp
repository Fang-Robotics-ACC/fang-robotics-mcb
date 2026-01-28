#include "communication/i_bus/i_bus_channel_section.hpp"
#include "communication/i_bus/i_bus_channel_data.hpp"

#include <gtest/gtest.h>
namespace fang::communication::ibus::channelSectionTest
{

TEST(IBusChannelSection, deserialization)
{
    // This checks for proper deserialization by having expected values
    // being hardcoded from a series of bytes

    // 14 channels, 28 bytes
    ChannelSection section
    {{
        0x00, 0x01, //0x0100 in least endian format or 256
        0x10, 0x00, //0x0010 in least endian format or 16
        0x00, 0x01, //0x0100 in least endian format or 256
        0x10, 0x00, //0x0010 in least endian format or 16
        0x10, 0x00, //0x0010 in least endian format or 16
        0x10, 0x00, //0x0010 in least endian format or 16
        0x10, 0x00, //0x0010 in least endian format or 16
        0x00, 0x01, //0x0100 in least endian format or 256
        0x10, 0x00, //0x0010 in least endian format or 16
        0x00, 0x01, //0x0100 in least endian format or 256
        0x10, 0x00, //0x0010 in least endian format or 16
        0x10, 0x00, //0x0010 in least endian format or 16
        0x10, 0x00, //0x0010 in least endian format or 16
        0x10, 0x00  //0x0010 in least endian format or 16
    }};

    ChannelData expecteddata
    {
        256,
        16,
        256,
        16,
        16,
        16,
        16,    
        256,
        16,
        256,
        16,
        16,
        16,
        16
    };

    EXPECT_EQ(expecteddata, section.getChannelData());
}

TEST(ChannelSection, checkSum)
{
    // https://basejunction.wordpress.com/2015/08/23/en-flysky-i6-14-channels-part1/

    const uint16_t expectedCheckSum{0xf354};

    const ChannelSection channelSection
    {{
        0xdc, 0x05,
        0xdb, 0x05,
        0xEF, 0x03,
        0xdd, 0x05,
        0xd0, 0x07,
        0xd0, 0x07,
        0xdc, 0x05,
        0xdc, 0x05,
        0xdc, 0x05,
        0xdc, 0x05,
        0xdc, 0x05,
        0xdc, 0x05,
        0xdc, 0x05,
        0xdc, 0x05
    }};

    EXPECT_TRUE(channelSection.isValid(expectedCheckSum));
}
}