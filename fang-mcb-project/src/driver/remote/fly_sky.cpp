#include "fly_sky.hpp"
#include "tap/algorithms/math_user_utils.hpp"

namespace fang::remote
{
const math::CoolLerp FlySky::kNormalizer{{1000.0, -1.0}, {1000, 1.0}};

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
    setChannels(channelData);
    // Convert to joystick and switch data values
    // update commandMapper based off of those new values
}

void  FlySky::setChannels(communication::ibus::ChannelData channelData)
{
    for(int i{}; i < channelData.size(); ++i)
    {
        // To safeguard against floating point errors triggering out of bounds
        const double kNormalized{tap::algorithms::limitVal<double>(channelData[i], -1000.0, 1000.0)};
        channelValues_[i] = kNormalized;
    }
}
}