#include "robotmecanumlogic.hpp"
#include <cassert>
namespace logic
{
    namespace chassis
    {
        RobotMecanumLogic::RobotMecanumLogic(const Meters& horizontalWheelDistance,
                                             const Meters& verticalWheelDistance,
                                             const Meters& wheelRadius):
        mk_horizontalWheelDistance{horizontalWheelDistance},
        mk_verticalWheelDistance{verticalWheelDistance},
        mk_wheelRadius{wheelRadius}
        {
            assert(wheelRadius.to<double>() >= 0.0 && "Wheel radius must be positive");
            assert(horizontalWheelDistance.to<double>() >= 0.0 && "Chassis dimension must be positive");
            assert(verticalWheelDistance.to<double>() >= 0.0 && "Chassis dimension must be positive");
        }

        void RobotMecanumLogic::setMotion(const Velocity2D& translation, const RPM& rotation)
        {
            setTranslation(translation);
            setRotation(rotation);
        }

        void RobotMecanumLogic::setTranslation(const Velocity2D& translation)
        {
            m_translation = translation;
        }

        void RobotMecanumLogic::setRotation(const RPM& rotation)
        {
            m_rotation = rotation;
        }


        Velocity2D RobotMecanumLogic::getTranslation() const
        {
            return m_translation;
        }

        RPM RobotMecanumLogic::getRotation() const
        {
            return m_rotation;
        }

        QuadDriveData RobotMecanumLogic::getWheelSpeeds() const
        {
            return QuadDriveData{getFrontLeftWheelSpeed(), getFrontRightWheelSpeed(),
                                 getRearLeftWheelSpeed(),  getRearRightWheelSpeed()};
        }
        
        RPM RobotMecanumLogic::getFrontLeftWheelSpeed() const
        {
            //https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
            //Equation 20, but v_x is v_y and v_y is v_x
            //If all of v_x is positive, then the wheels are pushing in the same
            //direction. It is desired for this to be positive
            //How many radius's per second? i.e. radians persecond
            //w_1
            const RadianMetersPerSecond translationFactor{(m_translation.y + m_translation.x).to<double>()};
            const RadianMetersPerSecond rotationFactor{mk_wheelDistanceConstant * m_rotation};
            return ((1.0 / mk_wheelRadius) * (translationFactor - rotationFactor));
        }
        RPM RobotMecanumLogic::getFrontRightWheelSpeed() const
        {
            //https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
            //Equation 20, but v_x is v_y and v_y is v_x
            //If all of v_x is positive, then the wheels are pushing in the same
            //direction. It is desired for this to be positive
            //w_2
            const RadianMetersPerSecond translationFactor{(m_translation.y - m_translation.x).to<double>()};
            const RadianMetersPerSecond rotationFactor{mk_wheelDistanceConstant * m_rotation};
            return ((1.0 / mk_wheelRadius) * (translationFactor + rotationFactor));
        }

        RPM RobotMecanumLogic::getRearLeftWheelSpeed() const
        {
            //https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
            //Equation 20, but v_x is v_y and v_y is v_x
            //If all of v_x is positive, then the wheels are pushing in the same
            //direction. It is desired for this to be positive
            //w_3

            const RadianMetersPerSecond translationFactor{(m_translation.y - m_translation.x).to<double>()};
            const RadianMetersPerSecond rotationFactor{mk_wheelDistanceConstant * m_rotation};
            return ((1.0 / mk_wheelRadius) * (translationFactor - rotationFactor));
        }

        RPM RobotMecanumLogic::getRearRightWheelSpeed() const
        {
            //https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
            //Equation 20, but v_x is v_y and v_y is v_x
            //Equation 20, but v_x is v_y and v_y is v_x
            //If all of v_x is positive, then the wheels are pushing in the same
            //direction. It is desired for this to be positive
            //w_4

            const RadianMetersPerSecond translationFactor{(m_translation.y + m_translation.x).to<double>()};
            const RadianMetersPerSecond rotationFactor{mk_wheelDistanceConstant * m_rotation};
            return ((1.0 / mk_wheelRadius) * (translationFactor + rotationFactor));
        }
    }
}