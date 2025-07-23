#ifndef FANG_ROBOTICS_MCB_TRAP_IMU_HPP_SENSORS
#define FANG_ROBOTICS_MCB_TRAP_IMU_HPP_SENSORS
#include "wrap/units/units_alias.hpp"
#include "tap/communication/sensors/imu/imu_interface.hpp"

namespace trap::communication::sensors
{
    class Imu
    {
    public:
        using ImuInterface = tap::communication::sensors::imu::ImuInterface;

        Imu(ImuInterface& imu);

        Radians getPitch() const;
        Radians getYaw() const;
        Radians getRoll() const;
    private:
        ImuInterface& m_imu;
    };
}
#endif