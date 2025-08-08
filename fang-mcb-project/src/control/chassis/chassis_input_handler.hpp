#ifndef FANG_ROBOTICS_MCB_CHASSIS_INPUT_HANDLER_HPP
#define FANG_ROBOTICS_MCB_CHASSIS_INPUT_HANDLER_HPP
#include "util/math/linear/vector_alias.hpp"
#include "wrap/units/units_alias.hpp"

#include "tap/communication/serial/remote.hpp"

namespace fang::chassis 
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
         * Returns a clamped sum of the keyboard and mouse inputs
         */
        math::AbstractVector2D getTranslation() const;
        /**
         * Returns a clamped sum of the keyboard and mouse inputs
         */
        double getRotation() const;
        /**
         * Returns the desired translation motion
         * Depending on which mode is used, this could be relative to the robot chassis,
         * the field, or fang-mcb-project/src/wrap/rail/chassis/iholonomic_control.hpp
         * 
         */
        math::AbstractVector2D getRemoteTranslation() const;
        /**
         * Returns the key pressed. if multiple are pressed, the priority is
         * forward, backward, left right.
         */
        math::AbstractVector2D getKeyboardTranslation() const;

        /**
         * How fast either the chassis or the turret should
         * be rotated
         */
        double getRemoteRotation() const;
    private:
        static constexpr double mk_abstractMax{1.0};
        static constexpr double mk_abstractMin{-1.0};
        static constexpr math::AbstractVector2D mk_forward{0.0, 1.0};
        static constexpr math::AbstractVector2D mk_backward{0.0, -1.0};
        static constexpr math::AbstractVector2D mk_left{-1.0, 0.0};
        static constexpr math::AbstractVector2D mk_right{1.0, 0.0};
        static constexpr math::AbstractVector2D mk_still{0.0, 0.0};
        Remote& m_remote;
        const RemoteConfig mk_remoteConfig;
        const KeyboardConfig mk_keyboardConfig;
    };
}//namespace fang::chassis 
#endif