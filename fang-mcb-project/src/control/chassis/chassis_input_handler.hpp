#ifndef FANG_ROBOTICS_MCB_CHASSIS_INPUT_HANDLER_HPP
#define FANG_ROBOTICS_MCB_CHASSIS_INPUT_HANDLER_HPP
#include "configuration/unitaliases.hpp"
#include "configuration/mathaliases.hpp"
#include "tap/communication/serial/remote.hpp"

namespace control
{
    namespace chassis
    {
        using Remote = tap::communication::serial::Remote;

        class ChassisInputHandler
        {
        public:
        struct RemoteConfig
        {
            Remote::Channel xTranslationChannel;
            Remote::Channel yTranslationChannel;
            Remote::Channel rotationChannel;
        };

        struct KeyboardConfig
        {
            Remote::Key forwardKey;
            Remote::Key backwardKey;
            Remote::Key leftKey;
            Remote::Key rightKey;
        };

        struct Config
        {
            RemoteConfig remoteConfig;
            KeyboardConfig keyboardConfig;
        };

            ChassisInputHandler(Remote& remote, const Config& config);
            /**
             * Returns the desired translation motion
             * Depending on which mode is used, this could be relative to the robot chassis,
             * the field, or the 
             * The barrel facing forward is the positive y direciton.
             * This interpets the dji remote inputs
             */
            math::AbstractVector2D getRemoteTranslation() const;

            /**
             * Returns the key pressed. if multiple are pressed, the priority is
             * forward, backward, left right.
             */
            math::AbstractVector2D getKeyboardTranslation() const;

            /**
             * Returns the amount that the turret should rotate
             */
            double getRemoteAngularDisplacement() const;

            /**
             * How fast either the chassis or the turret should
             * be rotated
             */
            double getRemoteRotation() const;
        private:

            static constexpr math::AbstractVector2D mk_forward{0.0, 1.0};
            static constexpr math::AbstractVector2D mk_backward{0.0, -1.0};

            static constexpr math::AbstractVector2D mk_left{-1.0, 0.0};
            static constexpr math::AbstractVector2D mk_right{1.0, 0.0};
            static constexpr math::AbstractVector2D mk_still{0.0, 0.0};

            Remote& m_remote;

            const RemoteConfig mk_remoteConfig;
            const KeyboardConfig mk_keyboardConfig;

        };
    }// namespace chassis
}//namespace control
#endif