#include "chassis_input_handler.hpp"

#include "unitaliases.hpp"
#include "mathaliases.hpp"
#include "chassislogicaliases.hpp"

namespace control
{
    namespace chassis
    {

        ChassisInputHandler::ChassisInputHandler(Remote& remote)
            : m_remote{remote}
        {}

        logic::chassis::Velocity2D ChassisInputHandler::getRemoteTranslation() const
        {
            const double leftJoystickHorizontal{m_remote.getChannel(Remote::Channel::LEFT_HORIZONTAL)};
            const MetersPerSecond xTranslation{mk_motionConfig.maxXTranslation * leftJoystickHorizontal};

            const double leftJoystickVertical{m_remote.getChannel(Remote::Channel::LEFT_VERTICAL)};
            const MetersPerSecond yTranslation{mk_motionConfig.maxYTranslation * leftJoystickVertical};

            return logic::chassis::Velocity2D{xTranslation, yTranslation};
        }

        Radians ChassisInputHandler::getRemoteAngularDisplacement() const
        {
            const double rightJoystickHorizontal{m_remote.getChannel(Remote::Channel::RIGHT_HORIZONTAL)};
            return mk_motionConfig.maxAngularDisplacement * rightJoystickHorizontal;
        }

        RPM ChassisInputHandler::getRemoteRotation() const
        {
        const double rightJoystickHorizontal{m_remote.getChannel(Remote::Channel::RIGHT_HORIZONTAL)};
        return mk_motionConfig.maxRotation * rightJoystickHorizontal;
        }
    }// namespce chassis
}// namespace control