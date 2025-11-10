#include "wrap/trap/algorithms/ipid_modder.hpp"
#include "wrap/rail/telemetry/iangular_position_telemetry.hpp"

#include <memory>
#include <cmath>

namespace fang::turret
{
/**
 * This assumes the head is somewhat balanced.
 * 
 * sine is zero
 * 
 * If the robot's head is tilted backwards, it needs a forward force
 * if the robot's head is tilted forwards, it needs a backwards force
 * 
 * If you do the math it's related to trigonometry
 * 
 * Output needs to be an arithmetic type
 * 
 * WARNING: This assumes that zero is level (no compensation needed)
 */
template <typename Output> 
class TiltPidModder : public trap::algorithms::IPidModder<Output>
{
public:
    /**
     * @param scalingConstant: This scales the sine of the angle
     */
    struct Config
    {
        double correctionScaler
    };

    /**
     * This needs to provide the angular position relative to gravity.
     * 
     * fieldPitchSensor should be zero when the turret head or balanced object
     * is level.
     * 
     * Tilted down should be a negative angle (if need be, the scalingConstant)
     */
    TiltPidModder(std::unique_ptr<telemetry::IAngularPosition> fieldPitchSensor, const Config& config):
        fieldPitchSensor_{std::move(fieldPitchSensor)},
        config_{config}
    {}

    /**
     * Note that this strips the unit protection of the fieldPitchSensor.
     * The scaling constant is coupled to the raw value.
     */
    Output getModdedOutput(const Output& output) override
    {
        // These calculations are not unit sensitive
        const double kRawAngle{static_cast<double>(fieldPitchSensor_->getAngularPosition())};

        // Solve for the equilibrium of an tall object hinged at the bottom
        // which is under the influence of gravity
        // The moment at the hinge should keep it in equilibrium in all positions

        // If the head is tilted down, the angle is negative, a positive force must counteract it
        // Therefore, a negative is required.
        // This provides the archetype
        const double kPhysicsCorrection{-std::sin(kRawAngle)};

        // It must be scaled to various turret head sizes
        const double kCorrection{config_.correctionScaler * kPhysicsCorrection};

        // The turret is targeting a specific position, but
        // The correct should remove the influence of gravity
        // So that its ability to achieve the desired position is unhindered
        return static_cast<Output>{kCorrection} + output;
    };
private:
    std::unique_ptr<telemetry::IAngularPosition> fieldPitchSensor_;
    Config config_;
};
}