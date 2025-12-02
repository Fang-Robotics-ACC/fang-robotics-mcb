#ifndef FANG_ROBOTICS_MCB_PIERCE_CHASSIS_INPUT_CONFIG_HPP
#define FANG_ROBOTICS_MCB_PIERCE_CHASSIS_INPUT_CONFIG_HPP
#include "control/chassis/chassis_input_handler.hpp"
namespace fang::robot
{

    using Remote = tap::communication::serial::Remote;
    using Channel = Remote::Channel;
    using Key = Remote::Key;

    static const chassis::ChassisInputHandler::RemoteConfig k_chassisInputRemoteConfig
    {
        Channel::LEFT_HORIZONTAL,   //xTranslation
        Channel::LEFT_VERTICAL,     //yTranslation
        Channel::WHEEL              //rotation
    };

    static const chassis::ChassisInputHandler::KeyboardConfig k_chassisInputKeyboardConfig
    {
        Key::W, //forward
        Key::S, //backward
        Key::A, //left
        Key::D  //right
    };

    static const chassis::ChassisInputHandler::Config kChassisInputConfig
    {
        k_chassisInputRemoteConfig,
        k_chassisInputKeyboardConfig
    };
}
#endif