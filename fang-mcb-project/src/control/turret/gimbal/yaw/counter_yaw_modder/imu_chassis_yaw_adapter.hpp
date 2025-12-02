#pragma once
#include "wrap/rail/telemetry/iangular_velocity_telemetry.hpp"
#include "wrap/trap/communication/sensors/iimu.hpp"

namespace fang::telemetry
{
class ImuChassisYawVelocityAdapter : public IAngularVelocity
{
public:
    using Imu = trap::communication::sensors::IImu;
    ImuChassisYawVelocityAdapter(std::unique_ptr<Imu> imu):
        imu_{std::move(imu)}
    {}

    RPM getAngularVelocity() const override
    {
        return imu_->getAngularVelocityZ();
    }

private:
    std::unique_ptr<Imu> imu_;
};
}