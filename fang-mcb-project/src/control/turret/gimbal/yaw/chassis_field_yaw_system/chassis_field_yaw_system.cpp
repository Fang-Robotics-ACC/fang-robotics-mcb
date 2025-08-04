#include "chassis_field_yaw_system.hpp"

namespace fang::turret
{

    ChassisFieldYawSystem::ChassisFieldYawSystem
    (
        std::unique_ptr<Motor> motor,
        std::unique_ptr<Imu> imu,
        const Config& config
    ):
        motor_{std::move(motor)},
        chassisImu_{std::move(imu)},
        kYawError_{config.yawError}
    {
    }

    void ChassisFieldYawSystem::initialize()
    {
        motor_->initialize();
    }

    void ChassisFieldYawSystem::update()
    {
        motor_->update();
    }

    void ChassisFieldYawSystem::setTargetFieldYaw(const Radians& yaw)
    {
        const Radians kChassisYaw{chassisImu_->getYaw()};
        // If the chassis is 90 degrees counterclockwise to the field
        // And the field yaw is zero, then the robotwise yaw needs to be 
        // -90 degrees
        const Radians kRobotwiseYaw{yaw - kChassisYaw};
        setChassiswiseYaw(kRobotwiseYaw);
    }

    void ChassisFieldYawSystem::setChassiswiseYaw(const Radians& yaw)
    {
        // If the zero position of the motor is 5 degrees counterclockwise
        // to the field yaw zero, the error would be 5 degrees counterclockwise
        // Thus, the fed position towards the turret would be -5 degrees counterclockwise

        const Radians kFieldYaw{yaw - kYawError_};
        motor_->setTargetPosition(kFieldYaw);
    }
}