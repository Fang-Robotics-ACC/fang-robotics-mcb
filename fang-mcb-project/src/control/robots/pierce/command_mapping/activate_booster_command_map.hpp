#ifndef FANG_ROBOTICS_MCB_ACTIVATE_BOOSTER_COMMAND_MAP_HPP
#define FANG_ROBOTICS_MCB_ACTIVATE_BOOSTER_COMMAND_MAP_HPP
#include "tap/control/remote_map_state.hpp"
namespace control
{
    static const tap::control::RemoteMapState k_activateBoosterRemoteState
    {
        tap::communication::serial::Remote::Switch::LEFT_SWITCH,
        tap::communication::serial::Remote::SwitchState::UP
    };

}
#endif