#include "chassis_input_handler.hpp"

#include "unitaliases.hpp"
#include "mathaliases.hpp"

namespace control
{
    namespace chassis
    {

        ChassisInputHandler::ChassisInputHandler(Remote& remote)
            : m_remote{remote}
        {
        }

        math::AbstractVector2D ChassisInputHandler::getRemoteTranslation() const
        {
            const double xTranslationScale{m_remote.getChannel(Remote::Channel::LEFT_HORIZONTAL)};
            const double yTranslationScale{m_remote.getChannel(Remote::Channel::LEFT_VERTICAL)};

            return math::AbstractVector2D{xTranslationScale, yTranslationScale};
        }

        double ChassisInputHandler::getRemoteAngularDisplacement() const
        {
            //Counterclockwise is positiev
            const double angularDisplacementScale{-m_remote.getChannel(Remote::Channel::WHEEL)};
            return angularDisplacementScale;
        }

        double ChassisInputHandler::getRemoteRotation() const
        {
            const double rotationScale{-m_remote.getChannel(Remote::Channel::WHEEL)};
            return rotationScale;
        }
    }// namespce chassis
}// namespace control