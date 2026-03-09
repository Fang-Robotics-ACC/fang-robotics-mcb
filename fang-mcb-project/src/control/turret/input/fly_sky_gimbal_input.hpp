#pragma once

#include "wrap/rail/turret/igimbal_input.hpp"

#include "driver/remote/fly_sky.hpp"
namespace fang::turret
{
    class FlySkyGimbalInput : public IGimbalInput
    {
    public:
        using Remote = remote::FlySky;
        struct Config
        {
            Remote::Channel pitchChannel;
            Remote::Channel yawChannel;
        };

        FlySkyGimbalInput(Remote& remote, const Config& config);

        double getPitch() const override;
        /**
         * Counterclockwise is positive, clockwise is negative
         * (Math convention.)
         */
        double getYaw() const override;
    private:
        static constexpr double kAbstractMin{-1.0};
        static constexpr double kAbstractMax{1.0};

        static constexpr double kFiringWheelThreshold{750};
        Remote& remote_;
        const Config kConfig_;
    };
}