#ifndef MECANUM_MOTION_CALCULATOR_H_YEET_YEET_SDLFJSELKFJ
#define MECANUM_MOTION_CALCULATOR_H_YEET_YEET_SDLFJSELKFJ
#include "quaddrivedata.h"
#include "translation2d.h"
#include "unitaliases.hpp"
#include "modm/math/geometry/vector.hpp"
#include "chassislogicaliases.h"

namespace logic
{
    namespace chassis
    {
        /**
         * This assumes that the wheels are at 45 degrees.
         * This uses the equations from this paper
         * https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
         * This assumes the radius of the wheels are 1
         */

        class BaseMecanumMotionCalculator
        {
        public:
            BaseMecanumMotionCalculator(){}
            void setQuadDriveData(const QuadDriveData& quadDriveData);
            /**
             * Returns the movement of the robot relative to the robot.
             * Refer to field mecanum calculator to get the translation relative
             * to a field.
             */
            Translation2D getTranslation() const;
            /**
             * If the mecanum drive is to be assumed to be a tank
             * drive, there would be a difference between the overrall
             * left and right speeds of the left and right tank tracks.
             */
            double getLateralDifference() const;
        private:
            QuadDriveData m_quadDriveData{0,0,0,0};
        };
    }
}
#endif