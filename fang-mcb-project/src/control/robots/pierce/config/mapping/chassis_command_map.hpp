#ifndef FANG_ROBOTICS_MCB_PIERCE_CHASSIS_COMMAND_MAP_HPP
#define FANG_ROBOTICS_MCB_PIERCE_CHASSIS_COMMAND_MAP_HPP
#include "tap/control/remote_map_state.hpp"
namespace control
{
    using Remote = tap::communication::serial::Remote;
    using SwitchState = Remote::SwitchState;
    using Key = Remote::Key;
    //This is the state of the right switch to activate choosing a command for the chassis
    static const SwitchState k_chassisRightSwitchContext{SwitchState::DOWN};

    static const SwitchState k_fieldMecanumLeftSwitchActivate{SwitchState::MID};
    static const SwitchState k_fieldShurikenLeftSwitchActivate{SwitchState::UP};

    static const tap::control::RemoteMapState k_fieldMecanumRemoteState
    {
        k_chassisRightSwitchContext,
        k_fieldMecanumLeftSwitchActivate
    };

    static const tap::control::RemoteMapState k_shurikenModeRemoteState
    {
        k_chassisRightSwitchContext,
        k_fieldShurikenLeftSwitchActivate
    };

    static const tap::control::RemoteMapState k_fieldMecanumKeyboardState
    {
        {Key::E}
    };

    static const tap::control::RemoteMapState k_shurikenModeKeyboardState
    {
        {Key::Q}
    };
}
#endif