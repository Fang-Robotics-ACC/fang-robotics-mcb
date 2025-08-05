#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_MECANUM_MECANUM_CALCULATOR_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_MECANUM_MECANUM_CALCULATOR_HPP
#include "abstract_mecanum_calculator.hpp"
#include "wrap/units/units_alias.hpp"

#include "modm/math/geometry/vector.hpp"
namespace fang::chassis
{
    /**
     * This uses the equations from this paper
     * https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
     */
    class MecanumCalculator
    {
    public:
        MecanumCalculator(const Meters& horizontalWheelDistance,
                          const Meters& verticalWheelDistance,
                          const Meters& wheelRadius);
        void setWheelSpeeds(const QuadRPM& quadDriveData);
        /**
         * Returns the movement of the robot relative to the robot.
         */
        Velocity2D getTranslation() const;
        /**
         * Counterclockwise is positive
         */
        RPM getRotation() const;
    private:
        QuadSpeedsRadPersec quadDriveData_{RPM{0}, RPM{0}, RPM{0}, RPM{0}};
        AbstractMecanumCalculator abstractMecanumCalculator_{};
        //l_x + l_y
        const Meters kwheelDistanceConstant_;
        const Meters kWheelRadius_;
    };
}
#endif