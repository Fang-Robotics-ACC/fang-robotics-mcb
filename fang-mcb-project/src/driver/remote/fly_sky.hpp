#pragma once

namespace fang::remote
{

/**
 * Based off of the information here
 * https://github.com/GOFIRST-Robotics/northstar-robomaster/blob/main/northstar-robomaster-project/src/communication/serial/fly_sky.hpp
 */
class FlySky
{
public:
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
};
}