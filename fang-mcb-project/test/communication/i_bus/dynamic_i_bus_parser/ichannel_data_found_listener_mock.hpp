#pragma once

#include "communication/i_bus/dynamic_i_bus_parser/ichannel_data_found_listener.hpp"
#include <gmock/gmock.h>

namespace fang::communication::ibus 
{
class IChannelDataFoundListenerMock : public IChannelDataFoundListener
{
public:
    MOCK_METHOD(void, channelDataFound, (const ChannelData& channelData), (override));
};
}
