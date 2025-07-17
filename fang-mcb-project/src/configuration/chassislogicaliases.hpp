#ifndef CHASSIS_LOGIC_ALISES_H_SDFSF_YEET_YEET
#define CHASSIS_LOGIC_ALISES_H_SDFSF_YEET_YEET
#include "control/chassis/data/quad_drive_data.hpp"
#include "util/math/linear/vector_2d.hpp"
#include "util/math/linear/vector_alias.hpp"
#include "unitaliases.hpp"
#include "modm/math/geometry/vector.hpp"

namespace chassis
{
    using AbstractQuadDriveData = RawQuadDriveData;
    using Translation2D = math::AbstractVector2D;

    //Messy for backward compatibility. Will be refactored during the next refactor cycle
    //Oof.
    using Velocity2D = math::Vector2D<MetersPerSecond>;
}
#endif