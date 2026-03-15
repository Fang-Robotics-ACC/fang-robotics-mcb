#include "ballistics_aim_command.hpp"

#include "tap/algorithms/math_user_utils.hpp"
#include "tap/algorithms/ballistics.hpp"
#include "tap/algorithms/transforms/transform.hpp"

#include <cmath>

namespace fang::turret
{
    using namespace units::literals;
    BallisticsAimCommand::BallisticsAimCommand(FieldGimbalSubsystem& gimbal, trap::communication::sensors::IImu& cameraOrientationImu, const Config& config)
        :   
        config_{config},
        gimbal_{gimbal},
        cameraOrientationImu_{cameraOrientationImu}
    {
        addSubsystemRequirement(&gimbal_);
    }

    void BallisticsAimCommand::initialize()
    {
    }

    void BallisticsAimCommand::basicTargetFound(const BasicTargetT& basicTarget)
    {
        currentTarget_ = basicTarget;
    }

    void BallisticsAimCommand::execute()
    {

        // WARNING: BLLALLISTICS API USES OUT PARAMETERS
        const Vector kGlobalTarget{cameraToGlobal({currentTarget_.x, currentTarget_.y, currentTarget_.z})};
        float calculatedTravelTime{};
        float calculatedTurretPitch{};
        float calculatedTurretYaw{};

    //const AbstractKinematicState &targetInitialState,
    //float bulletVelocity,
    //uint8_t numIterations,
    //float *turretPitch,
    //float *turretYaw,
    //float *projectedTravelTime,
    //const float pitchAxisOffset)
        const bool kSuccess
        {
            tap::algorithms::ballistics::findTargetProjectileIntersection
            (
                tap::algorithms::ballistics::SecondOrderKinematicState //target state
                {
                    {kGlobalTarget.x(), kGlobalTarget.y(), kGlobalTarget.z()},
                    {0,0,0},
                    {0,0,0}
                },
                MetersPerSecond{config_.bulletVelocity}.to<double>(),
                2, //iterations
                &calculatedTravelTime,
                &calculatedTurretPitch,
                &calculatedTurretYaw,
                0.0
            )
            
        };
        const Radians kTargetPitch{calculatedTurretPitch};
        const Radians kTargetYaw{calculatedTurretYaw};

        gimbal_.setTargetFieldPitch(kTargetPitch);
        gimbal_.setTargetFieldYaw(kTargetYaw);
    }

    BallisticsAimCommand::Vector BallisticsAimCommand::cameraToGlobal(const Vector& cameraCoordinates) const
    {
        // Currently, this only applys a rotation transform
        // Shift ofset will requrie a lot more math.
        // The robot should roughly point in the right direction still
        // reverse gimbal orientation for global
        Transform correction
        {
            Position{0,0,0},
            Orientation
            {
                0.0,
                -static_cast<double>(cameraOrientationImu_.getPitch()), 
                -static_cast<double>(cameraOrientationImu_.getYaw())
            }
        };
        return correction.apply(cameraCoordinates);
    }

    void BallisticsAimCommand::end(bool interrupted)
    {
    }

    bool BallisticsAimCommand::isFinished() const
    {
        //Default command must never finish
        return false;
    }
}