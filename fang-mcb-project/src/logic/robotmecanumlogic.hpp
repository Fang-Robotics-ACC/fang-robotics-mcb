#ifndef FANG_ROBOTICS_MCB_ROBOT_MECANUM_LOGIC_HPP
#define FANG_ROBOTICS_MCB_ROBOT_MECANUM_LOGIC_HPP
#include "unitaliases.hpp"
#include "quaddrivedata.hpp"
#include "abstractfieldmecanumlogic.hpp"
#include "chassislogicaliases.hpp"
#include "quaddrivedata.hpp"


namespace logic
{
    namespace chassis
    {
        class FieldMecanumLogic 
        {
        public:
        using QuadDriveData = data::chassis::QuadDriveData<RPM>;
        /**
         * Refer to: https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
         * in equation 24
         * The horizontalWheelDistance refers to twice as lx
         * The verticalWheelDistance refers to twice as ly
         * The vertical distance is parallel to the forward direction of the robot
         * The horizontal distance is parallel to the sideways direction of the robot 
         */
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

        Radians getRobotAngle() const;
        Velocity2D getTranslation() const;
        RPM getRotation() const;

        /**https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
         * This uses equation 20
         */
        QuadDriveData getWheelSpeeds() const;
        double getFrontRightWheelSpeed() const;
        double getFrontLeftWheelSpeed() const;
        double getRearLeftWheelSpeed() const;
        double getRearRightWheelSpeed() const;

        private:
        //This will not update translation. It can be dangerous because the user can expect
        //However, this can remove redundancy in internal implementation
        void rawSetRobotAngle(Radians robotAngle);
        
        Velocity2D fieldToRobotTranslation(const Velocity2D& translation) const;
        Velocity2D robotToFieldTranslation(const Velocity2D& translation) const;
        
        Radians m_robotAngle{0.0};

        const Meters mk_wheelRadius;
        const Meters mk_horizontalWheelDistance;
        const Meters mk_halfHorizontalWheelDistance{horizontalWheelDistance / 2.0};
        const Meters mk_verticalWheelDistance;
        const Meters mk_halfVerticalWheelDistance{verticalWheelDistance / 2.0};

        AbstractFieldMecanumLogic m_abstractFieldLogic{};
        };
    }
}
#endif