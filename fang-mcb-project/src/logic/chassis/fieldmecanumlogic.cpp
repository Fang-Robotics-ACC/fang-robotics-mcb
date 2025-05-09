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
        }

        void FieldMecanumLogic::setTotalMotion(const Velocity2D& translation, const RPM& rotation, const Radians& robotAngle)
        {

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