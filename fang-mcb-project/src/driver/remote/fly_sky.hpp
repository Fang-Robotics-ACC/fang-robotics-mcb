#pragma once

#include "tap/communication/serial/remote.hpp"

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
class FlySky
{
public:
    using TapRemote = tap::communication::serial::Remote;

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

    void initialize();
    void update() ;

    double getChannel(Channel channel) const;
    TapRemote::SwitchState getSwitch() const;
};
}