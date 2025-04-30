#ifndef UNITLESS_ROBOT_CENTRIC_MECANUM_LOGIC_H_SDLJLSKSKEFLJASD
#define UNITLESS_ROBOT_CENTRIC_MECANUM_LOGIC_H_SDLJLSKSKEFLJASD
#include "quaddrivedata.h"
#include "chassislogicaliases.h"
#include "quaddrivedata.h"

namespace logic
{
    namespace chassis
    {
        class UnitlessRobotMecanumLogic 
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
         */
        void setMotion(const Translation2D& translation, double rotation);
        QuadDriveData getWheelRotations() const;
        private:
        Translation2D m_translation{0,0};
        double m_rotation{0};
        };
    }
}
#endif