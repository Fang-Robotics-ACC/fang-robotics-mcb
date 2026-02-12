#pragma once

#include "util/math/linear/cool_lerp.hpp"
#include "tap/communication/serial/remote.hpp"
#include "driver/drivers.hpp"
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
        rightVertical,
        leftVertical,
        leftHorizontal,
        switchA,
        switchB,
        switchC,
        switchD,
        wheelA,
        wheelB 
    };

    enum class Switch
    {
        switchA,
        switchB,
        switchC,
        switchD 
    };

    FlySky(Drivers& drivers, coolSerial::ByteQueue& byteQueue);
    void update();

    void channelDataFound(const communication::ibus::ChannelData& channelData);

    TapRemote::SwitchState getTaprootSwitch(TapRemote::Switch switchId) const;
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

    Drivers& drivers_;
    communication::ibus::DynamicParser ibusParser_;
    ChannelValues channelValues_{};
};
}