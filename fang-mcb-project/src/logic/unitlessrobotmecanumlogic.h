#ifndef UNITLESS_ROBOT_CENTRIC_MECANUM_LOGIC_H_SDLJLSKSKEFLJASD
#define UNITLESS_ROBOT_CENTRIC_MECANUM_LOGIC_H_SDLJLSKSKEFLJASD

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
        void setMotion(double x, double y, double rotation);
        double getFrontLeftPercentage() const;
        double getFrontRightPercentage() const;
        double getRearLeftPercentage() const;
        double getRearRightPercentage() const;
        private:
        };
    }
}
#endif