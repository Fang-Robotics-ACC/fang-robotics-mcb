#include "fly_sky.hpp"
#include "tap/algorithms/math_user_utils.hpp"
#include "system/assert/fang_assert.hpp"

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

FlySky::TapRemote::SwitchState FlySky::getSwitch(Switch switchId) const
{
}

FlySky::TapRemote::SwitchState FlySky::getTaprootSwitch(TapRemote::Switch switchId) const
{
}


void  FlySky::setChannels(communication::ibus::ChannelData channelData)
{
    for(int i{0}; i < channelData.size(); ++i)
    {
        // To safeguard against floating point errors triggering out of bounds
        const double kNormalized{tap::algorithms::limitVal<double>(channelData[i], -1000.0, 1000.0)};
        channelValues_[i] = kNormalized;
    }
}

FlySky::TapRemote::SwitchState FlySky::channelToSwitchState(double channelData) const
{
    TapRemote::SwitchState switchState;

    // Slightly out of bounds to be tolerant to floating point errors
    // Adapted from UMN fly_sky drivers
    if (-0.25 <= channelData && channelData < 0.25)
    {
        switchState = TapRemote::SwitchState::DOWN;
    }
    else if (0.25 <= channelData && channelData < 0.75)
    {
        switchState = TapRemote::SwitchState::MID;
    }
    else if (0.75 <= channelData && channelData <= 1.25)
    {
        switchState = TapRemote::SwitchState::UP;
    }
    else
    {
        FANG_ASSERT(false, "invalid channelData, likely does not correspond to a switch");
    }
}
}