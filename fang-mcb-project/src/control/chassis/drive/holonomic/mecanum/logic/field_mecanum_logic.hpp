#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_MECANUM_LOGIC_FIELD_MECANUM_LOGIC_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_MECANUM_LOGIC_FIELD_MECANUM_LOGIC_HPP
#include "control/chassis/data/physics_alias.hpp"
#include "wrap/units/units_alias.hpp"
#include "robot_mecanum_logic.hpp"

using namespace units::literals;

namespace fang::chassis
{
    class FieldMecanumLogic
    {
    public:
        using Config = RobotMecanumLogic::Config;

        /**
         * Refer to: https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
         * in equation 24
         * The horizontalWheelDistance refers to twice as lx
         * The verticalWheelDistance refers to twice as ly
         * The vertical distance is parallel to the forward direction of the robot
         * The horizontal distance is parallel to the sideways direction of the robot
         */
        FieldMecanumLogic(const Config& config);

        FieldMecanumLogic(const Meters& horizontalWheelDistance,
                          const Meters& verticalWheelDistance,
                          const Meters& wheelRadius);
        /**
         * Refer to https://gm0.org/en/latest/docs/software/tutorials/mecanum-drive.html
         * The formula has been adapted so that the positive rotation is counter-clockwise.
         * Although this is does not smoothly translate joystick movements, it is mathematically
         * consistent with the convention that counter-clockwise. That is the main context
         * for MecanumLogic. With the IMU being involved, it is imperative that a single
         * rotational convention is used. And it is recommended that the mathematical ones
         * would be the choice.
         */
        void setMotion(const Velocity2D& translation, const RPM& rotation);
        void setTotalMotion(const Velocity2D& translation, const RPM& rotation, const Radians& robotAngle);
        /**
         * If the robot is facing forward at the field, that is 0 degrees.
         * If the robot is facing left from the forward field direction, that is +90 degrees
         * If the robot is racing right from the forward field direction that is -90 degrees
         */
        void setRobotAngle(const Radians& robotAngle);
        void setTranslation(const Velocity2D& translation);
        void setRotation(const RPM& rotation);
        const Radians&getRobotAngle() const;
        const Velocity2D& getTranslation() const;
        RPM getRotation() const;
        QuadRPM getWheelSpeeds() const;
    private:
        RPM getFrontRightWheelSpeed() const;
        RPM getFrontLeftWheelSpeed() const;
        RPM getRearLeftWheelSpeed() const;
        RPM getRearRightWheelSpeed() const;
        //This does not update the translation when the robot angle is changed.
        //It is useful in certain cases to speed stuff up.
        void rawSetRobotAngle(const Radians& rotation);
        Velocity2D fieldToRobotTranslation(const Velocity2D& translation) const;
        Velocity2D robotToFieldTranslation(const Velocity2D& translation) const;

        Radians robotAngle_{0.0};
        RobotMecanumLogic robotMecanumLogic_;
        Velocity2D fieldTranslation_{0_mps, 0_mps};
    };
}
#endif