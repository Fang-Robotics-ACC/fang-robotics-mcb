#pragma once
#include "communication/i_bus/i_bus_channel_data.hpp"
namespace fang::communication::ibus 
{
class IChannelDataFoundListener 
{
public:
    virtual void channelDataFound(const ChannelData& channelData) = 0;
    virtual ~IChannelDataFoundListener() = default;
};
}
