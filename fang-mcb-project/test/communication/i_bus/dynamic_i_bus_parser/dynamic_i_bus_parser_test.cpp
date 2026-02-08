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

    parser.update();
    EXPECT_CALL(dataFoundListener, channelDataFound(kExpectedData));
}
}