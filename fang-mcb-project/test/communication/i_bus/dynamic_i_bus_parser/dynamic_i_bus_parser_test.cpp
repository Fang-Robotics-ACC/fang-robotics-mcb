#include "communication/i_bus/dynamic_i_bus_parser/dynamic_i_bus_parser.hpp"
#include "communication/i_bus/i_bus_channel_section.hpp"

#include "cool_serial/byte_queue.hpp"
#include "ichannel_data_found_listener_mock.hpp"

#include <gtest/gtest.h>

namespace fang::communication::ibus::dynamicIbusParserTest
{
/**
 * Takes known ibus signals from :https://basejunction.wordpress.com/2015/08/23/en-flysky-i6-14-channels-part1/
 * and checks if it is parsed correctly :D
 */
TEST(DynamicParser, completeParse)
{
    const coolSerial::Bytes kKnownIbusFrame
    {
        0x20, 0x40, // sof header
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
        0xdc, 0x05,
        0x54, 0xf3  // checksum
    };

    const ChannelData kExpectedData
    {
        1500,
        1499,
        1007,
        1501,
        2000,
        2000,
        1500,
        1500,
        1500,
        1500,
        1500,
        1500,
        1500,
        1500
    };

    coolSerial::ByteQueue queue{std::deque<coolSerial::Byte>{kKnownIbusFrame.begin(), kKnownIbusFrame.end()}};
    testing::StrictMock<IChannelDataFoundListenerMock> dataFoundListener{};
    DynamicParser parser{queue, dataFoundListener};

    EXPECT_CALL(dataFoundListener, channelDataFound(kExpectedData));
    parser.update();
}

/**
 * Takes known ibus signals from :https://basejunction.wordpress.com/2015/08/23/en-flysky-i6-14-channels-part1/
 * and checks if it is parsed correctly :D
 */
TEST(DynamicParser, segmement)
{
    const ChannelData kExpectedData
    {
        1500,
        1499,
        1007,
        1501,
        2000,
        2000,
        1500,
        1500,
        1500,
        1500,
        1500,
        1500,
        1500,
        1500
    };

    coolSerial::ByteQueue queue{};
    testing::StrictMock<IChannelDataFoundListenerMock> dataFoundListener{};
    DynamicParser parser{queue, dataFoundListener};

    const coolSerial::Bytes kFrameSegment0 
    {
        0x20, 0x40, // sof header
    };

    queue.addBytes(kFrameSegment0);
    parser.update();

    const coolSerial::Bytes kFrameSegment1 
    {
        0xdc, 0x05,
        0xdb, 0x05,
        0xEF, 0x03,
        0xdd, 0x05,
    };

    queue.addBytes(kFrameSegment1);
    parser.update();

    const coolSerial::Bytes kFrameSegment2 
    {
        0xd0, 0x07,
        0xd0, 0x07,
        0xdc, 0x05,
        0xdc, 0x05,
        0xdc, 0x05,
        0xdc, 0x05,
        0xdc, 0x05,
        0xdc, 0x05,
        0xdc, 0x05,
        0xdc, 0x05,
    };

    queue.addBytes(kFrameSegment2);
    parser.update();

    const coolSerial::Bytes kFrameSegment3
    {
        0x54, 0xf3  // checksum
    };

    queue.addBytes(kFrameSegment3);
    EXPECT_CALL(dataFoundListener, channelDataFound(kExpectedData));
    parser.update();
}

/**
 * Takes known ibus signals from :https://basejunction.wordpress.com/2015/08/23/en-flysky-i6-14-channels-part1/
 * and checks if it is parsed correctly :D
 */
TEST(DynamicParser, invalidChecksum)
{
    const coolSerial::Bytes kKnownIbusFrame
    {
        0x20, 0x40, // sof header
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
        0xdc, 0x05,
        0x54, 0xf4  // invalid checksum (0xf4 is supposed to be 0xf3)
    };

    const ChannelData kExpectedData
    {
        1500,
        1499,
        1007,
        1501,
        2000,
        2000,
        1500,
        1500,
        1500,
        1500,
        1500,
        1500,
        1500,
        1500
    };

    coolSerial::ByteQueue queue{std::deque<coolSerial::Byte>{kKnownIbusFrame.begin(), kKnownIbusFrame.end()}};
    testing::StrictMock<IChannelDataFoundListenerMock> dataFoundListener{};
    DynamicParser parser{queue, dataFoundListener};

    // Expect no call since the checksum is invalid
    parser.update();
}
}