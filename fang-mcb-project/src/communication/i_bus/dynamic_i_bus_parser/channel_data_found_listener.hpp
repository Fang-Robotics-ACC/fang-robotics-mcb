#pragma once
#include "communication/i_bus/i_bus_channel_data.hpp"
namespace fang::communication::ibus 
{
class ChannelDataFoundListener 
{
public:
    virtual void channelDataFound() = 0;
    virtual ~ChannelDataFoundListener() {}
};
}
