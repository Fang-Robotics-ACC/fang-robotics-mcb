#ifndef FANG_ROBOTICS_MCB_PIERCE_TURRET_COMMAND_MAP_HPP
#define FANG_ROBOTICS_MCB_PIERCE_TURRET_COMMAND_MAP_HPP
#include "tap/control/remote_map_state.hpp"
namespace control
{
    using Remote = tap::communication::serial::Remote;
    static const tap::control::RemoteMapState k_activateBoosterRemoteState
    {
        Remote::Switch::LEFT_SWITCH,
        Remote::SwitchState::UP
    };

    static const tap::control::RemoteMapState k_deactivateBoosterRemoteState
    {
        Remote::Switch::LEFT_SWITCH,
        Remote::SwitchState::DOWN
    };
}
#endif