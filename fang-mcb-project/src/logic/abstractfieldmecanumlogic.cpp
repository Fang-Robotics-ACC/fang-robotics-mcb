#include "abstractfieldmecanumlogic.hpp"

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
            const Translation2D fieldTranslation{getTranslation()};
            m_robotAngle = robotAngle;
            //Update robot-centric translation to new angle
            setTranslation(fieldTranslation);
        }

        void AbstractFieldMecanumLogic::setTranslation(const Translation2D& translation)
        {
            //Counteract the robot's angle relative to the field
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
            //Reverse the rotation that had been appied to make the translation to
            //Be relative to the field and not the robot
            return robotToFieldTranslation(m_robotMecanumLogic.getTranslation());
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
            return rotateVector(translation, -m_robotAngle);
        }

        Translation2D AbstractFieldMecanumLogic::robotToFieldTranslation(const Translation2D& translation) const
        {
            //If the robot is facing left and needs to move forward relative to the field,
            //Then the motion vector that is relative to the robot facing forwward needs to be rotated
            //in the opposite angle
            return rotateVector(translation, m_robotAngle);
        }

        Translation2D AbstractFieldMecanumLogic::rotateVector(const Translation2D& vector, const Radians& rotationAngle) const
        {
            //Rotation matrix
            //https://www.youtube.com/watch?v=1oYEo7PNIBQ
            //I know it's Wikipedia but it's will help wwith the youtube video
            //In general, Wikipedia is pretty good as a math reference, too.
            //https://en.wikipedia.org/wiki/Rotation_matrix

            const double angle{rotationAngle.to<double>()};
            const double rotatedx{vector.x * (std::cos(angle)) - vector.y * (std::sin(angle))};
            const double rotatedy{vector.x * (std::sin(angle)) + vector.y * (std::cos(angle))};

            return Translation2D{rotatedx, rotatedy};
        }
    }
}