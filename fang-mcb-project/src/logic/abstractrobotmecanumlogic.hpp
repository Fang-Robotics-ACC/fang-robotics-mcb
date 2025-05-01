#ifndef ABSTRACT_ROBOT_CENTRIC_MECANUM_LOGIC_H_SDLJLSKSKEFLJASD
#define ABSTRACT_ROBOT_CENTRIC_MECANUM_LOGIC_H_SDLJLSKSKEFLJASD
#include "quaddrivedata.hpp"
#include "chassislogicaliases.hpp"
#include "quaddrivedata.hpp"

namespace logic
{
    namespace chassis
    {
        class AbstractRobotMecanumLogic 
        {
        public:
        /**
         * This is called RobotMecanumLogic because the frame
         * of reference is relative to the robot. It will always strafe
         * relative to the robot and not the field.
         * Translation is the percentage of the maximum speed 
         * Positive rotation is counterclockwise it a percentage
         * of the maximum speed that will be applied to offset
         * left and right sides to produce a rotation
         * (i.e. if the max speed is 100 f/s, then 0.5 will mean
         * that the difference between the overall motion of the left
         * and right sides of the drive will be by 50 f/s. A positive value
         * will mean the robot will rotate counterclockwise.)
         * 
         * 
         * Refer to https://gm0.org/en/latest/docs/software/tutorials/mecanum-drive.html
         * The formula has been adapted so that the positive rotation is counter-clockwise.
         * Although this is does not smoothly translate joystick movements, it is mathematically
         * consistent with the convention that counter-clockwise. That is the main context
         * for MecanumLogic. With the IMU being involved, it is imperative that a single
         * rotational convention is used. And it is recommended that the mathematical ones
         * would be the choice.
         */
        void setMotion(const Translation2D& translation, double rotationalOffset);
        void setTranslation(const Translation2D& translation);
        void setRotationOffset(double rotationalOffset);

        Translation2D getTranslation() const;
        double getRotationOffset() const;

        QuadDriveData getWheelSpeeds() const;
        double getFrontRightWheelSpeed() const;
        double getFrontLeftWheelSpeed() const;
        double getRearLeftWheelSpeed() const;
        double getRearRightWheelSpeed() const;
        private:
        Translation2D m_translation{0,0};
        double m_rotationalOffset{0};
        };
    }
}
#endif