#ifndef FANG_ROBOTICS_MCB_MECANUM_CALCULATOR_HPP
#define FANG_ROBOTICS_MCB_MECANUM_CALCULATOR_HPP
#include "quaddrivedata.hpp"
#include "translation2d.hpp"
#include "unitaliases.hpp"
#include "modm/math/geometry/vector.hpp"
#include "chassislogicaliases.hpp"
#include "abstractmecanumcalculator.hpp"

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
            QuadDriveData m_quadDriveData{RPM{0}, RPM{0}, RPM{0}, RPM{0}};
            AbstractMecanumCalculator m_abstractCalc{};
            //l_x + l_y
            const Meters mk_wheelDistanceConstant;
            const Meters mk_wheelRadius;
        };
    }
}
#endif