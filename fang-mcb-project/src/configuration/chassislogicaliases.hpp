#ifndef CHASSIS_LOGIC_ALISES_H_SDFSF_YEET_YEET
#define CHASSIS_LOGIC_ALISES_H_SDFSF_YEET_YEET
#include "quaddrivedata.hpp"
#include "translation2d.hpp"
#include "unitaliases.hpp"
#include "mathaliases.hpp"
#include "modm/math/geometry/vector.hpp"

namespace logic
{
    namespace chassis
    {
        using AbstractQuadDriveData = data::chassis::QuadDriveData<double>;
        using Translation2D = mathAliases::AbstractVector2D;

        //Messy for backward compatibility. Will be refactored during the next refactor cycle
        //Oof.
        using Velocity2D = modm::Vector<MetersPerSecond, 2>;

        using WheelDirection = modm::Vector<double, 2>;
    }
}
#endif