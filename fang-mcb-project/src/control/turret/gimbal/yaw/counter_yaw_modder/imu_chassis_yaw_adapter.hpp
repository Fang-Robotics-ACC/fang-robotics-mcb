#pragma once
#include "wrap/rail/telemetry/iangular_velocity_telemetry.hpp"
#include "wrap/trap/communication/sensors/iimu.hpp"

namespace fang::telemetry
{
class ImuChassisYawVelocityAdapter : public IAngularVelocity
{
public:
    ImuChassisYawVelocityAdapter(trap::communication::sensors::IImu imu):
        imu_{imu}
    {}

    RPM getAngularVelocity() const override
    {
        return imu_.getAngularVelocityZ();
    }

private:
    trap::communication::sensors::IImu& imu_;
};
}