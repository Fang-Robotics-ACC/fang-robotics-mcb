#ifndef FANG_ROBOTICS_MCB_MECANUM_CALCULATOR_HPP
#define FANG_ROBOTICS_MCB_MECANUM_CALCULATOR_HPP
#include "quaddrivedata.hpp"
#include "unitaliases.hpp"
#include "modm/math/geometry/vector.hpp"
#include "chassislogicaliases.hpp"
#include "control/chassis/mecanum/logic/abstract_mecanum_calculator.hpp"
#include "quaddrivedata.hpp"

namespace logic
{
    namespace chassis
    {
        using QuadDriveData = data::chassis::QuadDriveData<RPM>;
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

            void setWheelSpeeds(const QuadDriveData& quadDriveData);

            /**
             * Returns the movement of the robot relative to the robot.
             */
            Velocity2D getTranslation() const;

            /**
             * Counterclockwise is positive
             */
            RPM getRotation() const;
        private:
            data::chassis::QuadDriveData<RadiansPerSecond> quadDriveData_{RPM{0}, RPM{0}, RPM{0}, RPM{0}};
            ::chassis::AbstractMecanumCalculator abstractMecanumCalculator_{};
            //l_x + l_y
            const Meters kwheelDistanceConstant_;
            const Meters kWheelRadius_;
        };
    }
}
#endif