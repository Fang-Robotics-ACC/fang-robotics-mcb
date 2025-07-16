#ifndef FANG_ROBOTICS_MCB_ROBOT_MECANUM_LOGIC_HPP
#define FANG_ROBOTICS_MCB_ROBOT_MECANUM_LOGIC_HPP
#include "unitaliases.hpp"
#include "quaddrivedata.hpp"
#include "abstract_field_mecanum_logic.hpp"
#include "chassislogicaliases.hpp"
#include "quaddrivedata.hpp"

namespace chassis
{
    class RobotMecanumLogic 
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
    RPM getFrontRightWheelSpeed() const;
    RPM getFrontLeftWheelSpeed() const;
    RPM getRearLeftWheelSpeed() const;
    RPM getRearRightWheelSpeed() const;
    private:
    Velocity2D m_translation{MetersPerSecond{0.0}, MetersPerSecond{0.0}};
    RadiansPerSecond m_rotation{0};
    const Meters mk_wheelRadius;
    const Meters mk_horizontalWheelDistance;
    const Meters mk_halfHorizontalWheelDistance{mk_horizontalWheelDistance / 2.0};
    const Meters mk_verticalWheelDistance;
    const Meters mk_halfVerticalWheelDistance{mk_verticalWheelDistance / 2.0};
    //l_x + l_y
    const Meters mk_wheelDistanceConstant{mk_halfVerticalWheelDistance + mk_halfHorizontalWheelDistance};
    };
}
#endif