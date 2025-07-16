#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_MECANUM_LOGIC_ABSTRACT_MECANUM_CALCULATOR_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_MECANUM_LOGIC_ABSTRACT_MECANUM_CALCULATOR_HPP
#include "quaddrivedata.hpp"
#include "unitaliases.hpp"
#include "modm/math/geometry/vector.hpp"
#include "chassislogicaliases.hpp"

namespace chassis
{
    /**
     * This provides values that "move" in the way that
     * can abstractly decribe mecanum movement without units.
     * It allows the programmer to send "intuitive" singals
     * without it being grounded in specific units.
     * The regular motion calculator takes the output from this
     * And applies the units/right side stuff from the equations 23-25
     * (23-24 it will multipy it by r, the radius)
     * (25 it will multiply it by the complicated term
     * so that the output would be in rad/s)
     * This assumes that the wheels are at 45 degrees.
     * This uses the equations from this paper
     * https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
     * This assumes the radius of the wheels are 1
     */
    class AbstractMecanumCalculator
    {
    public:
        AbstractMecanumCalculator(){}
        void setWheelSpeeds(const AbstractQuadDriveData& quadDriveData);
        /**
         * Returns the movement of the robot relative to the robot.
         * Refer to field mecanum calculator to get the translation relative
         * to a field.
         */
        Translation2D getTranslation() const;
        /**
         * If the mecanum drive is to be assumed to be a tank
         * drive, there would be a difference between the overrall
         * left and right speeds of the left and right tank tracks divided by two
         * (Because this offset will be applied to each side)
         * Imagine the left and right tank at 0 speed.
         * To apply a counterclockwise rotation, a lateral offset
         * of 0.25 is appllied to each side. The left track will be -0.25
         * The right track will be 0.25. The difference is 0.50.
         */
        double getRotationOffset() const;
    private:
        AbstractQuadDriveData m_quadDriveData{0,0,0,0};
    };
}
#endif