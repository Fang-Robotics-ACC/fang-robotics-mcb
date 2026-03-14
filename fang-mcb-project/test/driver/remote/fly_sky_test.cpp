#include "communication/i_bus/i_bus_channel_data.hpp"
#include "driver/remote/fly_sky.hpp"

#include "cool_serial/byte_queue.hpp"

#include "tap/drivers.hpp"
#include "tap/mock/command_mapper_mock.hpp"

#include <gtest/gtest.h>
namespace fang::remote::flySkyTest
{


TEST(fang_remote_FlySky, zeroTest)
{
    const communication::ibus::ChannelData kTest 
    {
        1500, // right horizontal
        1500, // right vertical 
        1007, // left vertical
        1501, // left horizontal
        1500, // switch A
        1500, // switch B
        1500, // switch C
        1500, // switch D
        1500, // wheel A
        1500, // wheel B
        1500,
        1500,
        1500,
        1500
    };

    coolSerial::ByteQueue queue{};
    tap::Drivers drivers{};
    tap::mock::CommandMapperMock commandMapper{&drivers};
    FlySky remote{commandMapper, queue};
    // Normally, this would be triggered by the IBusParser
    // TODO: Consider refactoring it to where it doesn't need the IBusParser
    // but will rely on external utilities

    EXPECT_CALL(commandMapper, handleKeyStateChange(
        0, // This remote cannot pass key data
        tap::communication::serial::Remote::SwitchState::MID,
        tap::communication::serial::Remote::SwitchState::MID,
        false, // No mouse click relayed
        false // No mouse click relayed
    ));

    remote.channelDataFound(kTest);

    EXPECT_DOUBLE_EQ(remote.getChannel(FlySky::Channel::rightHorizontal), 0.0);
    EXPECT_DOUBLE_EQ(remote.getChannel(FlySky::Channel::rightVertical), 0.0);
    EXPECT_DOUBLE_EQ(remote.getChannel(FlySky::Channel::leftVertical), -0.986); // https://www.johndcook.com/interpolator.html
    EXPECT_DOUBLE_EQ(remote.getChannel(FlySky::Channel::leftHorizontal), 0.002); // https://www.johndcook.com/interpolator.html
}
}