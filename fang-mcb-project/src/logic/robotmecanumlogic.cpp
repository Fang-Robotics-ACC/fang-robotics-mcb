#include "robotmecanumlogic.hpp"

namespace logic
{
    namespace chassis
    {
        
        RPM RobotMecanumLogic::getFrontLeftWheelSpeed() const
        {
            //https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
            //Equation 20, but v_x is v_y and v_y is v_x
            //If all of v_x is positive, then the wheels are pushing in the same
            //direction. It is desired for this to be positive
            //w_1
            const MetersPerSecond translationFactor{m_translation.y - m_translation.x};
            const MetersPerSecond rotationFactor{mk_wheelDistanceConstant * m_rotation * k_antiRadians};
            return (1.0 / mk_wheelRadius) * (translationFactor - rotationFactor);
        }

        RPM RobotMecanumLogic::getFrontRightWheelSpeed() const
        {
            //https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
            //Equation 20, but v_x is v_y and v_y is v_x
            //If all of v_x is positive, then the wheels are pushing in the same
            //direction. It is desired for this to be positive
            //w_2
            const MetersPerSecond translationFactor{m_translation.y + m_translation.x};
            const auto rotationFactor{mk_wheelDistanceConstant * m_rotation};
            return (1.0 / mk_wheelRadius) * (translationFactor + rotationFactor);
        }

        /*
        RPM RobotMecanumLogic::getRearLeftWheelSpeed() const
        {
            //https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
            //Equation 20, but v_x is v_y and v_y is v_x
            //If all of v_x is positive, then the wheels are pushing in the same
            //direction. It is desired for this to be positive
            //w_3
            const MetersPerSecond translationFactor{m_translation.y + m_translation.x};
            const MetersPerSecond rotationFactor{mk_wheelDistanceConstant * m_rotation};
            return RPM{(1.0 / mk_wheelRadius) * (translationFactor - rotationFactor)};
        }

        RPM RobotMecanumLogic::getRearRightWheelSpeed() const
        {

            //https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
            //Equation 20, but v_x is v_y and v_y is v_x
            //Equation 20, but v_x is v_y and v_y is v_x
            //If all of v_x is positive, then the wheels are pushing in the same
            //direction. It is desired for this to be positive
            //w_4
            const MetersPerSecond translationFactor{m_translation.y - m_translation.x};
            const MetersPerSecond rotationFactor{mk_wheelDistanceConstant * m_rotation};
            return RPM{(1.0 / mk_wheelRadius) * (translationFactor + rotationFactor)};
        }
        */

    }
}