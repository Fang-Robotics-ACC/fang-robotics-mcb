#pragma once

#include "wrap/rail/turret/igimbal_input.hpp"

#include "tap/communication/serial/remote.hpp"
namespace fang::turret
{
    class DjiGimbalInput : public IGimbalInput
    {
    public:
        using Remote = tap::communication::serial::Remote;
        struct RemoteConfig
        {
            Remote::Channel pitchChannel;
            Remote::Channel yawChannel;
            Remote::Channel rotationChannel;
        };

        struct MouseConfig
        {
            double pitchPercentagePerPx;
            double yawPercentagePerPx;
        };

        struct Config
        {
            RemoteConfig remoteConfig;
            MouseConfig mouseConfig;
        };

        DjiGimbalInput(Remote& remote, const Config& config);

        double getPitch() const override;
        /**
         * Counterclockwise is positive, clockwise is negative
         * (Math convention.)
         */
        double getYaw() const override;
        bool getFire() const;
    private:
        static constexpr double mk_abstractMin{-1.0};
        static constexpr double mk_abstractMax{1.0};

        double getRemotePitch() const;
        double getRemoteYaw() const;

        double getMousePitch() const;
        double getMouseYaw() const;
        static constexpr double mk_firingWheelThreshold{750};
        Remote& m_remote;

        const RemoteConfig mk_remoteConfig;
        const MouseConfig mk_mouseConfig;
    };
}