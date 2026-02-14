#ifndef FANG_ROBOTICS_MCB_PIERCE_CHASSIS_INPUT_CONFIG_HPP
#define FANG_ROBOTICS_MCB_PIERCE_CHASSIS_INPUT_CONFIG_HPP
#include "control/chassis/input/dji_holonomic_input_handler.hpp"
namespace fang::robot
{

    using Remote = tap::communication::serial::Remote;
    using Channel = Remote::Channel;
    using Key = Remote::Key;

    static const chassis::DjiHolonomicInputHandler::RemoteConfig k_chassisInputRemoteConfig
    {
        Channel::LEFT_HORIZONTAL,   //xTranslation
        Channel::LEFT_VERTICAL,     //yTranslation
        Channel::WHEEL              //rotation
    };

    static const chassis::DjiHolonomicInputHandler::KeyboardConfig k_chassisInputKeyboardConfig
    {
        Key::W, //forward
        Key::S, //backward
        Key::A, //left
        Key::D  //right
    };

    static const chassis::DjiHolonomicInputHandler::Config kChassisInputConfig
    {
        k_chassisInputRemoteConfig,
        k_chassisInputKeyboardConfig
    };
}
#endif