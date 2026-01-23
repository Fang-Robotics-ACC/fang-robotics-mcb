#include "communication/i_bus/i_bus_channel_section.hpp"
#include "communication/i_bus/i_bus_channel_data.hpp"

#include <gtest/gtest.h>
namespace fang::communication::iBusChannelSectionTest
{

TEST(IBusChannelSection, deserialization)
{
    // This checks for proper deserialization by having expected values
    // being hardcoded from a series of bytes

    // 14 channels, 28 bytes
    IBusChannelSection section
    {{
        0x00, 0x01, //0x0100 in least endian format or 256
        0x10, 0x00, //0x0010 in least endian format or 128
        0x00, 0x01, //0x0100 in least endian format or 256
        0x10, 0x00, //0x0010 in least endian format or 128
        0x10, 0x00, //0x0010 in least endian format or 128
        0x10, 0x00, //0x0010 in least endian format or 128
        0x10, 0x00, //0x0010 in least endian format or 128
        0x00, 0x01, //0x0100 in least endian format or 256
        0x10, 0x00, //0x0010 in least endian format or 128
        0x00, 0x01, //0x0100 in least endian format or 256
        0x10, 0x00, //0x0010 in least endian format or 128
        0x10, 0x00, //0x0010 in least endian format or 128
        0x10, 0x00, //0x0010 in least endian format or 128
        0x10, 0x00  //0x0010 in least endian format or 128
    }};

}
}