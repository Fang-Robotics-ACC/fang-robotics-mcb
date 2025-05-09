#include "fieldmecanumlogic.hpp"
#include "rotatevector2d.hpp"
#include "mathaliases.hpp"

namespace logic
{
    namespace chassis
    {
        FieldMecanumLogic::FieldMecanumLogic(const Meters& horizontalWheelDistance,
                                             const Meters& verticalWheelDistance,
                                             const Meters& wheelRadius):
        m_robotMecanumLogic{horizontalWheelDistance, verticalWheelDistance, wheelRadius}
        {}

        void FieldMecanumLogic::setMotion(const Velocity2D& translation, const RPM& rotation)
        {

            setTranslation(translation);
            setRotation(rotation);
        }

        void FieldMecanumLogic::setTotalMotion(const Velocity2D& translation, const RPM& rotation, const Radians& robotAngle)
        {
            //The raw robot angle must be set so that when the translation is being updated
            //to robot relative vectors, it has the proper angle
            rawSetRobotAngle(robotAngle);
            setMotion(translation, rotation);
        }


        void FieldMecanumLogic::setRobotAngle(const Radians& robotAngle)
        {
            rawSetRobotAngle(robotAngle);
            Velocity2D fieldTranslation{getTranslation()};
            //The translation relative to the robot must be updated since the robot is facing along a 
            //difference direction
            setTranslation(fieldTranslation);
        }

        void FieldMecanumLogic::setTranslation(const Velocity2D& translation)
        {
            m_robotMecanumLogic.setTranslation(fieldToRobotTranslation(translation));
        }

        void FieldMecanumLogic::setRotation(const RPM& rotation)
        {
            m_robotMecanumLogic.setRotation(rotation);
        }

        Radians FieldMecanumLogic::getRobotAngle() const
        {
            return m_robotAngle;
        }

        Velocity2D FieldMecanumLogic::getTranslation() const
        {
            //The robot mecanum logic stores the translation relative to the robot, not the field
            return robotToFieldTranslation(m_robotMecanumLogic.getTranslation());
        }

        RPM FieldMecanumLogic::getRotation() const
        {
            return m_robotMecanumLogic.getRotation(); 
        }


        QuadDriveData FieldMecanumLogic::getWheelSpeeds() const
        {
            return m_robotMecanumLogic.getWheelSpeeds();
        }

        RPM FieldMecanumLogic::getFrontRightWheelSpeed() const
        {
            return m_robotMecanumLogic.getFrontRightWheelSpeed();
        }

        RPM FieldMecanumLogic::getFrontLeftWheelSpeed() const
        {
            return m_robotMecanumLogic.getFrontLeftWheelSpeed();
        }

        RPM FieldMecanumLogic::getRearLeftWheelSpeed() const
        {
            return m_robotMecanumLogic.getRearLeftWheelSpeed();
        }

        RPM FieldMecanumLogic::getRearRightWheelSpeed() const
        {
            return m_robotMecanumLogic.getRearRightWheelSpeed();
        }

        void FieldMecanumLogic::rawSetRobotAngle(const Radians& rotation)
        {
            m_robotAngle = rotation;
        }

        Velocity2D FieldMecanumLogic::fieldToRobotTranslation(const Velocity2D& translation) const
        {
            //If the robot is facing left and needs to move forward relative to the field,
            //Then the motion vector that is relative to the robot facing forwward needs to be rotated
            //in the opposite angle

            //The rotation function does not use units
            //This assumes the units are in meters per second
            const mathAliases::AbstractVector2D unitlessTranslation{translation.x.to<double>(), translation.y.to<double>()};
            //Rotate stripped vector
            const mathAliases::AbstractVector2D rotated{util::math::rotateVector2D(unitlessTranslation, -m_robotAngle)};
            //Convert stripped vector back into vector of units
            return Velocity2D{Velocity2D::unit{rotated.x},Velocity2D::unit{rotated.y}};
        }

        Velocity2D FieldMecanumLogic::robotToFieldTranslation(const Velocity2D& translation) const
        {
            //If the robot is facing left and needs to move forward relative to the field,
            //Then the motion vector that is relative to the robot facing forwward needs to be rotated
            //in the opposite angle
            //This counteracts that effect in order to recover the field translation vector

            //The rotation function does not use units
            //This assumes the units are in meters per second
            const mathAliases::AbstractVector2D unitlessTranslation{translation.x.to<double>(), translation.y.to<double>()};
            //Rotate stripped vector
            const mathAliases::AbstractVector2D rotated{util::math::rotateVector2D(unitlessTranslation, m_robotAngle)};
            //Convert stripped vector back into vector of units
            return Velocity2D{Velocity2D::unit{rotated.x},Velocity2D::unit{rotated.y}};
        }
    }//namespace chassis
}//namespace logic