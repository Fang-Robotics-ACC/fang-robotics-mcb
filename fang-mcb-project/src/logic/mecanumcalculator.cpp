#include "mecanumcalculator.hpp"
namespace logic
{
    namespace chassis
    {

        //lx is half of the total horizontal distance between the wheels
        //ly is half of the total vertical distance between the wheels
        MecanumCalculator::MecanumCalculator(const Meters& horizontalWheelDistance, const Meters& verticalWheelDistance):
            mk_wheelDistanceConstant{horizontalWheelDistance / 2.0 + verticalWheelDistance / 2.0}
        {}
    }
}