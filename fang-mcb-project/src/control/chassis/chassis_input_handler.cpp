#include "chassis_input_handler.hpp"

#include "unitaliases.hpp"
#include "util/math/linear/vector_alias.hpp"

#include "tap/algorithms/math_user_utils.hpp"

namespace control
{
    namespace chassis
    {

        ChassisInputHandler::ChassisInputHandler(Remote& remote, const Config& config)
        :   m_remote{remote},
            mk_remoteConfig{config.remoteConfig},
            mk_keyboardConfig{config.keyboardConfig}
        {
        }

        math::AbstractVector2D ChassisInputHandler::getTranslation() const
        {
            const math::AbstractVector2D translationSum{getKeyboardTranslation() + getRemoteTranslation()};
            const double xClamped{tap::algorithms::limitVal<double>(translationSum.x, mk_abstractMin, mk_abstractMax)};
            const double yClamped{tap::algorithms::limitVal<double>(translationSum.y, mk_abstractMin, mk_abstractMax)};
            return math::AbstractVector2D{xClamped, yClamped};
        }

        double ChassisInputHandler::getRotation() const
        {
            return tap::algorithms::limitVal<double>(getRemoteRotation(), mk_abstractMin, mk_abstractMax);
        }

        math::AbstractVector2D ChassisInputHandler::getKeyboardTranslation() const
        {
            if (m_remote.keyPressed(mk_keyboardConfig.forwardKey))
            {
                return mk_forward;
            }
            else if(m_remote.keyPressed(mk_keyboardConfig.backwardKey))
            {
                return mk_backward;
            }
            else if(m_remote.keyPressed(mk_keyboardConfig.leftKey))
            {
                return mk_left;
            }
            else if(m_remote.keyPressed(mk_keyboardConfig.rightKey))
            {
                return mk_right;
            }
            else
            {
                return mk_still;
            }
        }

        math::AbstractVector2D ChassisInputHandler::getRemoteTranslation() const
        {
            const double xTranslationScale{m_remote.getChannel(mk_remoteConfig.xTranslationChannel)};
            const double yTranslationScale{m_remote.getChannel(mk_remoteConfig.yTranslationChannel)};

            return math::AbstractVector2D{xTranslationScale, yTranslationScale};
        }

        double ChassisInputHandler::getRemoteAngularDisplacement() const
        {
            //Counterclockwise is positiev
            const double angularDisplacementScale{-m_remote.getChannel(mk_remoteConfig.rotationChannel)};
            return angularDisplacementScale;
        }

        double ChassisInputHandler::getRemoteRotation() const
        {
            const double rotationScale{-m_remote.getChannel(mk_remoteConfig.rotationChannel)};
            return rotationScale;
        }
    }// namespce chassis
}// namespace control