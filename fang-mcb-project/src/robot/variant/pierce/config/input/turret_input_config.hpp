#ifndef FANG_ROBOTICS_MCB_TURRET_INPUT_CONFIG_HPP
#define FANG_ROBOTICS_MCB_TURRET_INPUT_CONFIG_HPP
#include "control/turret/input/dji_gimbal_input.hpp"
namespace fang::robot
{
    using Remote = tap::communication::serial::Remote;
    using Channel = Remote::Channel;

    static const turret::DjiGimbalInput::RemoteConfig k_turretInputRemoteConfig
    {
        Channel::RIGHT_VERTICAL,
        Channel::RIGHT_HORIZONTAL,
        Channel::WHEEL
    };

    static const turret::DjiGimbalInput::MouseConfig k_turretInputMouseConfig
    {
        .pitchPercentagePerPx   = 0.15,
        .yawPercentagePerPx     = 0.15
    };
    static const turret::DjiGimbalInput::Config kTurretInputConfig
    {
        k_turretInputRemoteConfig,
        k_turretInputMouseConfig
    };

}
#endif