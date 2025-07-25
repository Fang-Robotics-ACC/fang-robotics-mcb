#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_MECANUM_LOGIC_ABSTRACT_FIELD_MECANUM_LOGIC_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_MECANUM_LOGIC_ABSTRACT_FIELD_MECANUM_LOGIC_HPP
#include "abstract_robot_mecanum_logic.hpp"
#include "control/chassis/data/physics_alias.hpp"
#include "control/chassis/drive/quad_drive/data/quad_drive_data.hpp"

namespace fang::chassis
{
    /**
    * This is called Field Mecanum Logic because the frame
    * of refernce is relative to the field
    * Translation is the percentage of the maximum speed
    * Positive rotation is counterclockwise it a percentage
    * of the maximum speed that will be applied to offset
    * left and right sides to produce a rotation
    * (i.e. if the max speed is 100 f/s, then 0.5 will mean
    * that the difference between the overall motion of the left
    * and right sides of the drive will be by 50 f/s. A positive value
    * will mean the robot will rotate counterclockwise.)
    *
    * Refer to https://gm0.org/en/latest/docs/software/tutorials/mecanum-drive.html
    * The formula has been adapted so that the positive rotation is counter-clockwise.
    * Although this is does not smoothly translate joystick movements, it is mathematically
    * consistent with the convention that counter-clockwise. That is the main context
    * for MecanumLogic. With the IMU being involved, it is imperative that a single
    * rotational convention is used. And it is recommended that the mathematical ones
    * would be the choice.
    */
    class AbstractFieldMecanumLogic
    {
    public:
        using AbstractQuadDriveData = AbstractWheelSpeeds;

        void setMotion(const AbstractVelocity2D& translation, double rotationalOffset);

        void setTotalMotion(const AbstractVelocity2D& translation, double rotationOffset, const Radians& robotAngle);

        /**
            * If the robot is facing forward at the field, that is 0 degrees.
            * If the robot is facing left from the forward field direction, that is +90 degrees
            * If the robot is racing right from the forward field direction that is -90 degrees
            */
        void setRobotAngle(const Radians& robotAngle);
        void setTranslation(const AbstractVelocity2D& translation);
        void setRotationOffset(double rotationalOffset);

        Radians getRobotAngle() const;
        AbstractVelocity2D getTranslation() const;
        double getRotationOffset() const;

        AbstractQuadDriveData getWheelSpeeds() const;

    private:
        double getFrontRightWheelSpeed() const;
        double getFrontLeftWheelSpeed() const;
        double getRearLeftWheelSpeed() const;
        double getRearRightWheelSpeed() const;

        AbstractVelocity2D fieldToRobotTranslation(const AbstractVelocity2D& translation) const;
        AbstractVelocity2D robotToFieldTranslation(const AbstractVelocity2D& translation) const;

        Radians robotAngle_{0.0};
        AbstractVelocity2D fieldTranslation_{0.0,0.0};

        AbstractRobotMecanumLogic robotwiseMecanumLogic_{};
    };
}
#endif