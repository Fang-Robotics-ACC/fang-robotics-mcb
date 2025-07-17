#include "cool_lerp.hpp"

#include <cassert>
#include <cmath>

namespace math
{
    CoolLerp::CoolLerp(const Vector2D& dataPoint1, const Vector2D& dataPoint2)
    : mk_dataPoint1{dataPoint1}, mk_dataPoint2{dataPoint2}, mk_input_range{dataPoint2.x - dataPoint1.x}
    {
        //assert(mk_input_range >= 0 && "data point 2's input is greater than data point 1's input");
        ////We can use direct comparison since inf is only triggered when they equal 0, not some miniscule number.
        //assert(dataPoint2.x != dataPoint1.x && "Undefined slope");
    }

    double CoolLerp::interpolate(double input) const
    {
        //Set the input relative to the lowest input
        //This is done so that when the percentage is calculated,
        //it will be 0 if the input is equal to
        //dataPoint 1's input (the lesser of the two)
        //and 1 if the input is equal to dataPoint 2's input
        //the higher of the two 
        const double leastDataInput{mk_dataPoint1.x} ;
        const double shiftedInput{input - leastDataInput};
        const double percentage{shiftedInput / mk_input_range};

        return std::lerp(mk_dataPoint1.y, mk_dataPoint2.y, percentage);
    }
}