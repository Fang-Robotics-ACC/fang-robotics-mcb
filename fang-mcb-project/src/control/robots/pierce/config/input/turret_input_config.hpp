#ifndef FANG_ROBOTICS_MCB_TURRET_INPUT_CONFIG_HPP
#define FANG_ROBOTICS_MCB_TURRET_INPUT_CONFIG_HPP
#include "control/turret/turret_input_handler.hpp"
namespace control
{
    using Remote = tap::communication::serial::Remote;
    using Channel = Remote::Channel;

    static const turret::TurretInputHandler::RemoteConfig k_turretInputRemoteConfig
    {
        Channel::RIGHT_VERTICAL,
        Channel::RIGHT_HORIZONTAL,
        Channel::WHEEL
    };

    static const turret::TurretInputHandler::MouseConfig k_turretInputMouseConfig
    {
        10,
        10
    };
    static const turret::TurretInputHandler::Config k_turretInputConfig
    {
        k_turretInputRemoteConfig,
        k_turretInputMouseConfig
    };

}
#endif