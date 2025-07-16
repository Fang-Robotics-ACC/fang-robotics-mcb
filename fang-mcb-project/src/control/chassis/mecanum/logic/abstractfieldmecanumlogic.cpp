#include "abstractfieldmecanumlogic.hpp"
#include "rotatevector2d.hpp"

#include <cmath>

namespace logic
{
    namespace chassis
    {
        void AbstractFieldMecanumLogic::setMotion(const Translation2D& translation, double rotationOffset)
        {
            setRotationOffset(rotationOffset);
            setTranslation(translation);
        }

        void AbstractFieldMecanumLogic::setTotalMotion(const Translation2D& translation, double rotationOffset, const Radians& robotAngle)
        {
            setRobotAngle(robotAngle);
            setRotationOffset(rotationOffset);
            setTranslation(translation);
        }

        void AbstractFieldMecanumLogic::setRobotAngle(const Radians& robotAngle)
        {
            //This must be obtained beforehand or else the new angle will result
            //in bogus being returned (the old field translation is relative to the old angle
            //not the new one.)
            m_robotAngle = robotAngle;
            //Update robot-centric translation to new angle
            setTranslation(m_fieldTranslation);
        }

        void AbstractFieldMecanumLogic::setTranslation(const Translation2D& translation)
        {
            //Counteract the robot's angle relative to the field
            m_fieldTranslation = translation;
            m_robotMecanumLogic.setTranslation(fieldToRobotTranslation(translation));
        }

        void AbstractFieldMecanumLogic::setRotationOffset(double rotationOffset)
        {
            m_robotMecanumLogic.setRotationOffset(rotationOffset);
        }

        Radians AbstractFieldMecanumLogic::getRobotAngle() const
        {
            return m_robotAngle;
        }

        Translation2D AbstractFieldMecanumLogic::getTranslation() const
        {
            return m_fieldTranslation;
        }

        double AbstractFieldMecanumLogic::getRotationOffset() const
        {
            return m_robotMecanumLogic.getRotationOffset();
        }


        Translation2D AbstractFieldMecanumLogic::fieldToRobotTranslation(const Translation2D& translation) const
        {
            //If the robot is facing left and needs to move forward relative to the field,
            //Then the motion vector that is relative to the robot facing forwward needs to be rotated
            //in the opposite angle
            return util::math::rotateVector2D(translation, -m_robotAngle);
        }

        Translation2D AbstractFieldMecanumLogic::robotToFieldTranslation(const Translation2D& translation) const
        {
            //If the robot is facing left and needs to move forward relative to the field,
            //Then the motion vector that is relative to the robot facing forwward needs to be rotated
            //in the opposite angle
            return util::math::rotateVector2D(translation, m_robotAngle);
        }

        double AbstractFieldMecanumLogic::getFrontRightWheelSpeed() const
        {
            return m_robotMecanumLogic.getFrontRightWheelSpeed();
        }

        double AbstractFieldMecanumLogic::getFrontLeftWheelSpeed() const
        {
            return m_robotMecanumLogic.getFrontLeftWheelSpeed();
        }

        double AbstractFieldMecanumLogic::getRearLeftWheelSpeed() const
        {
            return m_robotMecanumLogic.getRearLeftWheelSpeed();
        }

        double AbstractFieldMecanumLogic::getRearRightWheelSpeed() const
        {
            return m_robotMecanumLogic.getRearRightWheelSpeed();
        }

        AbstractQuadDriveData AbstractFieldMecanumLogic::getWheelSpeeds() const
        {
            return m_robotMecanumLogic.getWheelSpeeds();
        }
    }
}