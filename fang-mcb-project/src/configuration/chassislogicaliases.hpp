#ifndef CHASSIS_LOGIC_ALISES_H_SDFSF_YEET_YEET
#define CHASSIS_LOGIC_ALISES_H_SDFSF_YEET_YEET
#include "quaddrivedata.hpp"
#include "translation2d.hpp"
#include "unitaliases.hpp"
#include "modm/math/geometry/vector.hpp"

namespace logic
{
    namespace chassis
    {
        using QuadDriveData = data::chassis::QuadDriveData<double>;
        using Translation2D = modm::Vector<double,2>;
        using WheelDirection = modm::Vector<double, 2>;
    }
}
#endif