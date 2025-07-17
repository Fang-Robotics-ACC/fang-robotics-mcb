#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_MECANUM_LOGIC_ROBOT_MECANUM_LOGIC_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_MECANUM_LOGIC_ROBOT_MECANUM_LOGIC_HPP
#include "abstract_field_mecanum_logic.hpp"
#include "chassislogicaliases.hpp"
#include "quaddrivedata.hpp"
#include "unitaliases.hpp"

namespace chassis
{
    class RobotMecanumLogic
    {
    public:
        using QuadDriveData = data::chassis::QuadDriveData<RPM>;

        struct Config
        {
            const Meters& horizontalWheelDistance;
            const Meters& verticalWheelDistance;
            const Meters& wheelRadius;
        };
        /**
         * Refer to: https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
         * in equation 24
         * The horizontalWheelDistance refers to twice as lx
         * The verticalWheelDistance refers to twice as ly
         * The vertical distance is parallel to the forward direction of the robot
         * The horizontal distance is parallel to the sideways direction of the robot
         */
        RobotMecanumLogic(const Config& config);

        RobotMecanumLogic(const Meters& horizontalWheelDistance,
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
        void setTranslation(const Velocity2D& translation);
        void setRotation(const RPM& rotation);
        const Velocity2D& getTranslation() const;
        RPM getRotation() const;

        /**https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
         * This uses equation 20
         */
        QuadDriveData getWheelSpeeds() const;

    private:
        RPM getFrontRightWheelSpeed() const;
        RPM getFrontLeftWheelSpeed() const;
        RPM getRearLeftWheelSpeed() const;
        RPM getRearRightWheelSpeed() const;

        Velocity2D translation_{MetersPerSecond{0.0}, MetersPerSecond{0.0}};
        RadiansPerSecond rotation_{0};
        const MetersPerRadians kWheelRadius_; //Required for the math to work, "how many meters for each radius?"
        const Meters kHorizontalWheelDistance_;

        //https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
        //These are the constants used within the euqation
        const Meters kHalfHorizontalWheelDistance_{kHorizontalWheelDistance_ / 2.0};
        const Meters kVerticalWheelDistance_;
        const Meters kHalfVerticalWheelDistance_{kVerticalWheelDistance_ / 2.0};
        //l_x + l_y
        const MetersPerRadians kWheelDistanceConstant_{(kHalfVerticalWheelDistance_ + kHalfHorizontalWheelDistance_) / Radians{1}}; //The chassis is a larger "wheel"
    };
}
#endif