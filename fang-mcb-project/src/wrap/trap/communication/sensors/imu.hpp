#ifndef FANG_ROBOTICS_MCB_TRAP_IMU_HPP_SENSORS
#define FANG_ROBOTICS_MCB_TRAP_IMU_HPP_SENSORS
#include "iimu.hpp"
#include "wrap/units/units_alias.hpp"
#include "tap/communication/sensors/imu/imu_interface.hpp"

#include "tap/util_macros.hpp"
namespace trap::communication::sensors
{
    class Imu : public IImu
    {
    public:
        using ImuInterface = tap::communication::sensors::imu::ImuInterface;

        Imu(ImuInterface& imu);

        Radians getPitch() const override;
        Radians getYaw() const override;
        Radians getRoll() const override;
    private:
        ImuInterface& m_imu;
    };
}
#endif