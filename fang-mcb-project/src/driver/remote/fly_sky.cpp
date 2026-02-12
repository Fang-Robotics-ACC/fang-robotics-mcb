#include "fly_sky.hpp"
#include "tap/algorithms/math_user_utils.hpp"
#include "system/assert/fang_assert.hpp"

namespace fang::remote
{
const math::CoolLerp FlySky::kNormalizer{{1000.0, -1.0}, {1000, 1.0}};

FlySky::FlySky(tap::control::CommandMapper& commandMapper, coolSerial::ByteQueue& byteQueue)
    :
    commandMapper_{commandMapper},
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

    commandMapper_.handleKeyStateChange(
        0, // This remote cannot pass key data
        getTaprootSwitch(TapRemote::Switch::LEFT_SWITCH),
        getTaprootSwitch(TapRemote::Switch::RIGHT_SWITCH),
        false, // No mouse click relayed
        false // No mouse click relayed
    );
}

FlySky::TapRemote::SwitchState FlySky::getSwitch(Switch switchId) const
{
    double channelData{};
    switch(switchId)
    {

        case Switch::A:
            channelData = getChannel(Channel::switchA);
            break;
        case Switch::B:
            channelData = getChannel(Channel::switchB);
            break;
        case Switch::C:
            channelData = getChannel(Channel::switchC);
            break;
        case Switch::D:
            channelData = getChannel(Channel::switchD);
            break;
    }
    return channelToSwitchState(channelData);
}

FlySky::TapRemote::SwitchState FlySky::getTaprootSwitch(TapRemote::Switch switchId) const
{
    switch(switchId)
    {
        case TapRemote::Switch::LEFT_SWITCH:
            return getSwitch(Switch::B);
            break;
        case TapRemote::Switch::RIGHT_SWITCH:
            return getSwitch(Switch::C);
            break;
    }
}

double FlySky::getChannel(Channel channel) const
{
    return channelValues_[static_cast<int>(channel)];
}

void  FlySky::setChannels(communication::ibus::ChannelData channelData)
{
    for(int i{0}; i < static_cast<int>(channelData.size()); ++i)
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

    return switchState;
}
}