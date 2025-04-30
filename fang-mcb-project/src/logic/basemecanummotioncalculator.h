#ifndef MECANUM_MOTION_CALCULATOR_H_YEET_YEET_SDLFJSELKFJ
#define MECANUM_MOTION_CALCULATOR_H_YEET_YEET_SDLFJSELKFJ
#include "quaddrivedata.h"
#include "translation2d.h"
#include "modm/math/geometry/vector2.hpp"

namespace logic
{
    namespace chassis
    {
        template <typename Speed>
        using QuadDriveData = data::chassis::QuadDriveData
        using Translation2D = modm::Vector<Speed> 
        using WheelDirection = modm::Vector<double> 
        class BaseMecanumMotionCalculator
        {
        public:
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
            Speed getLateralDifference() const;
        };
    }
}
#endif