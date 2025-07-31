
#ifndef FANG_ROBOTICS_MCB_WRAP_TRAP_COMMUNICATION_SENSORS_IIMU_HPP_
#define FANG_ROBOTICS_MCB_WRAP_TRAP_COMMUNICATION_SENSORS_IIMU_HPP_
#include "wrap/units/units_alias.hpp"
namespace trap::communication::sensors
{
    /**
     * IMU interface with dimensional analysis
     */
    class IImu
    {
    public:
        virtual Radians getPitch() const = 0;
        virtual Radians getYaw() const = 0;
        virtual Radians getRoll() const = 0;
        virtual ~IImu() {};
    };
}
#endif // WRAP_TRAP_COMMUNICATION_SENSORS_IIMU_HPP_