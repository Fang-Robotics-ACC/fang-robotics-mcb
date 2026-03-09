#include "control/turret/input/fly_sky_gimbal_input.hpp"

#include "tap/algorithms/math_user_utils.hpp"

namespace fang::turret
{
    FlySkyGimbalInput::FlySkyGimbalInput(Remote& remote, const Config& config)
    :   remote_{remote},
        kConfig_{config}
    {
    }

    double FlySkyGimbalInput::getPitch() const
    {
        const double kPitch{remote_.getChannel(kConfig_.pitchChannel)};
        return tap::algorithms::limitVal<double>(kPitch, kAbstractMin, kAbstractMax);
    }

    double FlySkyGimbalInput::getYaw() const
    {
        const double kYaw{-remote_.getChannel(kConfig_.yawChannel)};
        return tap::algorithms::limitVal<double>(kYaw, kAbstractMin, kAbstractMax);
    }
}