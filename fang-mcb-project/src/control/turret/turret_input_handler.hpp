#ifndef FANG_ROBOTICS_MCB_TURRET_INPUT_HANDLER_HPP
#define FANG_ROBOTICS_MCB_TURRET_INPUT_HANDLER_HPP
#include "tap/communication/serial/remote.hpp"
namespace control
{
    namespace turret
    {
        class TurretInputHandler
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

            TurretInputHandler(Remote& remote, const Config& config);

            double getPitch() const;
            double getYaw() const;
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
}
#endif