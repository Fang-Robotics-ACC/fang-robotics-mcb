#pragma once
#include "wrap/trap/algorithms/ipid_modder.hpp"
#include "wrap/rail/telemetry/iangular_velocity_telemetry.hpp"

#include <memory>
#include <cmath>

namespace fang::turret
{
/**
 * 
 * If the turret's base is moving one way, the correction should be
 * in the opposite direction
 * 
 * WARNING: This assumes that the rotation convention is the same
 * for both the chassis sensor and the turret
 * 
 * The 
 */
class CounterYawModder : public trap::algorithms::IPidModder<RPM>
{
public:
    /**
     * @param correctionScale: This allows finely scaling
     * the desired counterrotation
     */
    struct Config
    {
        double correctionScale = 1.0;
    };

    /**
     * This needs to provide the angular position relative to gravity.
     * 
     * Whatever can provide the velocity of the base yaw, even adapters
     * can be fed as the telemetry
     * 
     * (for turret imu only robots, this can be estimated through inverse kinematics of the wheels)
     */
    CounterYawModder(std::unique_ptr<telemetry::IAngularVelocity> baseYawVelocitySensor, const Config& config):
        baseYawVelocitySensor_{std::move(baseYawVelocitySensor)},
        config_{config}
    {}

    /**
     * Note that this strips the unit protection of the fieldPitchSensor.
     * The scaling constant is coupled to the raw value.
     */
    RPM getModdedOutput(const RPM& output) override
    {
        // These calculations are not unit sensitive
        const RPM kBaseSpeed{baseYawVelocitySensor_->getAngularVelocity()};
        const RPM kCounterRotation{-kBaseSpeed};

        // Account for slight innacuracies
        const RPM kCorrection{config_.correctionScale * kCounterRotation};

        // The turret is targeting a specific position, but
        // the rotation of the base should not affect the final position
        // or else it would keep chasing said positoin
        return output + kCorrection;
    };
private:
    std::unique_ptr<telemetry::IAngularVelocity> baseYawVelocitySensor_;
    Config config_;
};
}