#ifndef ABSTRACT_FIELD_CENTRIC_MECANUM_LOGIC_H
#define ABSTRACT_FIELD_CENTRIC_MECANUM_LOGIC_H
#include "unitaliases.hpp"
#include "quaddrivedata.hpp"
#include "abstractrobotmecanumlogic.hpp"
#include "chassislogicaliases.hpp"
#include "quaddrivedata.hpp"


namespace logic
{
    namespace chassis
    {
        class AbstractFieldMecanumLogic 
        {
        public:
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

        void setTotalMotion(const Translation2D& translation, double rotationOffset, const Radians& robotAngle);

        /**
         * If the robot is facing forward at the field, that is 0 degrees. 
         * If the robot is facing left from the forward field direction, that is +90 degrees
         * If the robot is racing right from the forward field direction that is -90 degrees
         */
        void setRobotAngle(const Radians& robotAngle);
        void setTranslation(const Translation2D& translation);
        void setRotationOffset(double rotationalOffset);

        Radians getRobotAngle() const;
        Translation2D getTranslation() const;
        double getRotationOffset() const;

        AbstractQuadDriveData getWheelSpeeds() const;
        double getFrontRightWheelSpeed() const;
        double getFrontLeftWheelSpeed() const;
        double getRearLeftWheelSpeed() const;
        double getRearRightWheelSpeed() const;

        private:
        Translation2D fieldToRobotTranslation(const Translation2D& translation) const;
        Translation2D robotToFieldTranslation(const Translation2D& translation) const;
        
        Radians m_robotAngle{0.0};
        Translation2D m_fieldTranslation{0.0,0.0};

        AbstractRobotMecanumLogic m_robotMecanumLogic{};
        };
    }
}
#endif