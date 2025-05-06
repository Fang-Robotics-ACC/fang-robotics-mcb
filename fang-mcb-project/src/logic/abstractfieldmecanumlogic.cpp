#include "abstractfieldmecanumlogic.hpp"

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
            m_robotAngle = robotAngle;
            //Update robot-centric translation to new angle
            setTranslation(m_fieldTranslation);
        }

        void AbstractFieldMecanumLogic::setTranslation(const Translation2D& translation)
        {
            m_fieldTranslation = translation;
            Translation2D robotTranslation = m_fieldTranslation;
            //Counteract the robot's angle relative to the field
            m_robotMecanumLogic.setTranslation(robotTranslation.rotate(-m_robotAngle.to<double>()));
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
            Translation2D robotTranslation = m_robotMecanumLogic.getTranslation();
            //Reverse the rotation that had been appied to make the translation to
            //Be relative to the field and not the robot
            return robotTranslation.rotate(m_robotAngle.to<double>());
        }

        double AbstractFieldMecanumLogic::getRotationOffset() const
        {
            return m_rotationOffset;
        }

    }
}