#pragma once

#include "util/math/linear/cool_lerp.hpp"
#include "tap/communication/serial/remote.hpp"
#include "tap/control/command_mapper.hpp"
#include "communication/i_bus/i_bus_channel_data.hpp"
#include "communication/i_bus/dynamic_i_bus_parser/ichannel_data_found_listener.hpp"
#include "communication/i_bus/dynamic_i_bus_parser/dynamic_i_bus_parser.hpp"

namespace fang::remote
{

/**
 * Based off of the information here
 * https://github.com/GOFIRST-Robotics/northstar-robomaster/blob/main/northstar-robomaster-project/src/communication/serial/fly_sky.hpp
 * 
 * 
 * Note that Switch B updates the commandMappe LEFT_SWICH and Switch C updates the RIGHT_SWITCH
 * WARNING: switch A, B, and D can only be up or down, switch C is the only one that can have a center option.
 * 
 * TODO: Consider combining switch A and B to provide for up, middle, and down, then a 4th default state
 */
class FlySky : communication::ibus::IChannelDataFoundListener
{
public:
    using TapRemote = tap::communication::serial::Remote;
    // So that it can store then as normalzied decimals
    using ChannelValues = std::array<double, communication::ibus::kChannelCount>;

    enum class Channel 
    {
        rightHorizontal = 0,
        rightVertical = 1,
        leftVertical = 2,
        leftHorizontal = 3,
        wheelA = 4,
        wheelB = 5,
        switchC = 6,
        switchD = 7,
        switchA = 8,
        switchB = 9 
    };

    /**
     * Note: the reason we are breaking away from the normal enum class
     * naming convention is because they are single letters
     * 
     * Switch::A looks clearer than Switch::a
     * 
     * k is not needed for it is an enum class
     * 
     * Switch::switchA just looks redundant
     */
    enum class Switch
    {
        A,
        B,
        C,
        D,
        wheelA,
        wheelB
    };

    /**
     * The commandMapper is what listens for remoteStateChanges in order to know what mappings to trigger
     * generally, you are using the one in the Drivers singleton. (As much as taproot locked some architectural elements
     * to use drivers everywhere, requiring a singleton CommandMaper CommandScheduler, this code is designed to use only
     * what it needs for ease of testing and minimizing coupling.)
     */
    FlySky(tap::control::CommandMapper& commandMapper, coolSerial::ByteQueue& byteQueue);
    void update();

    void channelDataFound(const communication::ibus::ChannelData& channelData);

    /**
     * This is required to inform the command mapper of switch state changes.
     * 
     * It can only access switch B and switch C (LEFT_SWITCH and RIGHT_SWITCH)
     * respectively
     */
    TapRemote::SwitchState getTaprootSwitch(TapRemote::Switch switchId) const;

    /**
     * This can access all switches
     */
    TapRemote::SwitchState getSwitch(Switch switchId) const;
    double getChannel(Channel channel) const;
private:
    static const math::CoolLerp kNormalizer;
    static constexpr int kBaudrate{115200};
    /**
     * Normalizes channels
     */
    void setChannels(communication::ibus::ChannelData channelData);
    TapRemote::SwitchState channelToSwitchState(double channelData) const;

    tap::control::CommandMapper& commandMapper_;
    communication::ibus::DynamicParser ibusParser_;
    ChannelValues channelValues_{};
};
}