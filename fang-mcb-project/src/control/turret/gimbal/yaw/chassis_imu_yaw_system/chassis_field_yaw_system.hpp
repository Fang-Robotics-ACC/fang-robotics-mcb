#pragma once

#include "wrap/trap/communication/sensors/iimu.hpp"
#include "wrap/rail/turret/ifield_yaw_system.hpp"
#include "wrap/rail/motor/iposition_motor.hpp"

#include <memory>

namespace fang::turret
{
    /**
     * Assume that with the axis pointing up, the positive
     * yaw counterclockwise
     */
    class ChassisFieldYawSystem : virtual public IFieldYawSystem
    {
    public:
        using Motor = motor::IPositionMotor;
        using Imu = trap::communication::sensors::IImu;
        /**
         * @var yawError - corrects the
         * zero position of the motor. If the motor's zero
         * position 5 degrees counterclockwise, the error 
         * would be 5 degrees.
         */
        struct Config
        {
            Radians yawCorrection;
        };

        ChassisFieldYawSystem
        (
            std::unique_ptr<Motor> motor,
            std::unique_ptr<Imu> imu,
            const Config& config
        );
        void initialize() override;
        void update() override;
        void setTargetFieldYaw(const Radians& yaw) override;
    private:
        /**
         * Relative to the robot. So 90 degrees would set the rotation
         * 90 degrees relative to the robot.
         */
        void setChassiswiseYaw(const Radians& yaw);
        std::unique_ptr<Motor> motor_;
        std::unique_ptr<Imu> imu_;
        const Radians kYawError_;
    };
}