#ifndef CHASSIS_LOGIC_ALISES_H_SDFSF_YEET_YEET
#define CHASSIS_LOGIC_ALISES_H_SDFSF_YEET_YEET
#include "quaddrivedata.hpp"
#include "vector2d.hpp"
#include "unitaliases.hpp"
#include "mathaliases.hpp"
#include "modm/math/geometry/vector.hpp"

namespace logic
{
    namespace chassis
    {
        using AbstractQuadDriveData = data::chassis::QuadDriveData<double>;
        using QuadDriveData = data::chassis::QuadDriveData<RPM>;
        using Translation2D = math::AbstractVector2D;

        //Messy for backward compatibility. Will be refactored during the next refactor cycle
        //Oof.
        using Velocity2D = data::math::Vector2D<MetersPerSecond>;

        using WheelDirection = modm::Vector<double, 2>;
    }
}

namespace chassis
{
    using Translation2D = logic::chassis::Translation2D; //Patch to make refactoring more smooth
    using AbstractQuadDriveData = logic::chassis::AbstractQuadDriveData;
    using Velocity2D = logic::chassis::Velocity2D;
    using WheelDirection = logic::chassis::WheelDirection;
    using QuadDriveData = logic::chassis::QuadDriveData;
}
#endif