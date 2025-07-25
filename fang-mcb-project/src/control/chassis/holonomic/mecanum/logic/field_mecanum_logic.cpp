#include "field_mecanum_logic.hpp"
#include "util/math/geometry/rotate_vector_2d.hpp"

namespace fang::chassis
{
    FieldMecanumLogic::FieldMecanumLogic(const Config& config):
        FieldMecanumLogic(config.horizontalWheelDistance,
                          config.verticalWheelDistance,
                          config.wheelRadius)
    {
    }

    FieldMecanumLogic::FieldMecanumLogic(const Meters& horizontalWheelDistance,
                                         const Meters& verticalWheelDistance,
                                         const Meters& wheelRadius):
        robotMecanumLogic_{horizontalWheelDistance, verticalWheelDistance, wheelRadius}
    {
    }

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
        //The translation relative to the robot must be updated since the robot is facing along a
        //difference direction
        setTranslation(fieldTranslation_);
    }

    void FieldMecanumLogic::setTranslation(const Velocity2D& translation)
    {
        fieldTranslation_ = translation;
        robotMecanumLogic_.setTranslation(fieldToRobotTranslation(translation));
    }

    void FieldMecanumLogic::setRotation(const RPM& rotation)
    {
        robotMecanumLogic_.setRotation(rotation);
    }

    const Radians& FieldMecanumLogic::getRobotAngle() const
    {
        return robotAngle_;
    }

    const Velocity2D& FieldMecanumLogic::getTranslation() const
    {
        //The robot mecanum logic stores the translation relative to the robot, not the field
        return fieldTranslation_;
    }

    RPM FieldMecanumLogic::getRotation() const
    {
        return robotMecanumLogic_.getRotation();
    }

    WheelSpeeds FieldMecanumLogic::getWheelSpeeds() const
    {
        return robotMecanumLogic_.getWheelSpeeds();
    }

    void FieldMecanumLogic::rawSetRobotAngle(const Radians& rotation)
    {
        robotAngle_ = rotation;
    }
    Velocity2D FieldMecanumLogic::fieldToRobotTranslation(const Velocity2D& translation) const
    {
        //If the robot is facing left and needs to move forward relative to the field,
        //Then the motion vector that is relative to the robot facing forwward needs to be rotated
        //in the opposite angle
        //The rotation function does not use units
        //This assumes the units are in meters per second
        const math::AbstractVector2D unitlessTranslation{translation.x.to<double>(), translation.y.to<double>()};
        //Rotate stripped vector
        const math::AbstractVector2D rotated{math::rotateVector2D(unitlessTranslation, -robotAngle_)};
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
        const math::AbstractVector2D unitlessTranslation{translation.x.to<double>(), translation.y.to<double>()};
        //Rotate stripped vector
        const math::AbstractVector2D rotated{math::rotateVector2D(unitlessTranslation, robotAngle_)};
        //Convert stripped vector back into vector of units
        return Velocity2D{Velocity2D::unit{rotated.x},Velocity2D::unit{rotated.y}};
    }
}//namespace chassis