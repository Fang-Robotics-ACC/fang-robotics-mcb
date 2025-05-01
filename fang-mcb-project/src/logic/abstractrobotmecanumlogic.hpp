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
         */
        void setMotion(const Translation2D& translation, double rotationalOffset);
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