#include "fly_sky.hpp"

namespace fang::remote
{
FlySky::FlySky(Drivers& drivers, coolSerial::ByteQueue& byteQueue)
    :
    drivers_{drivers},
    ibusParser_{byteQueue, *this}
{
}

void FlySky::update()
{
    ibusParser_.update();
}

void FlySky::channelDataFound(const communication::ibus::ChannelData& channelData)
{
    // For ease, the channel data is normalized 
    // Normalize channel data
    // Convert to joystick and switch data values
    // update commandMapper based off of those new values
}
}