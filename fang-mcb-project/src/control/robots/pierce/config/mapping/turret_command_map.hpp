#ifndef FANG_ROBOTICS_MCB_PIERCE_TURRET_COMMAND_MAP_HPP
#define FANG_ROBOTICS_MCB_PIERCE_TURRET_COMMAND_MAP_HPP
#include "tap/control/remote_map_state.hpp"
namespace control
{
    using Remote = tap::communication::serial::Remote;
    using Key = Remote::Key;
    using MouseButton = tap::control::RemoteMapState::MouseButton;
    static const tap::control::RemoteMapState k_activateBoosterRemoteState
    {
        Remote::Switch::LEFT_SWITCH,
        Remote::SwitchState::UP
    };

    static const tap::control::RemoteMapState k_autofireRemoteState
    {
        Remote::SwitchState::UP,
        Remote::SwitchState::UP
    };

    static const tap::control::RemoteMapState k_unjamRemoteState
    {
        Remote::SwitchState::UP,
        Remote::SwitchState::DOWN
    };

    static const tap::control::RemoteMapState k_autofireMouseState
    {
        MouseButton::LEFT
    };

    static const tap::control::RemoteMapState k_unjamMouseState
    {
        MouseButton::RIGHT
    };
}
#endif