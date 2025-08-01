#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_DRIVE_QUAD_DRIVE_BASE_QUAD_DRIVE_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_DRIVE_QUAD_DRIVE_BASE_QUAD_DRIVE_HPP
#include "control/chassis/drive/quad_drive/quad_drive_subsystem.hpp"
#include "control/chassis/drive/quad_drive/data/quad_collection.hpp"
#include "driver/drivers.hpp"
#include "wrap/rail/rail_motor_owner.hpp"

#include <array>
#include <memory>

namespace fang::chassis
{
    /**
     * This provides control for a set of 4 ISpeedMotors
     * It manages the initialization and update functionality
     * as well.
     *
     * This is often passed into a holonomic drive or tank drive
     * to delegate managing the wheel speeds and updating each of the motors
     *
     * This can be managed by a taproot command (can be registered).
     */
    class BaseQuadDrive : public QuadDriveSubsystem
    {
    public:
        using Motor = motor::ISpeedMotor;
        using Motors = QuadCollection<std::unique_ptr<Motor>>;

        BaseQuadDrive
        (
            Drivers& drivers,
            std::unique_ptr<Motor> frontLeftMotor,
            std::unique_ptr<Motor> frontRightMotor,
            std::unique_ptr<Motor> rearLeftMotor,
            std::unique_ptr<Motor> rearRightMotor
        );

        /**
         * Motors should be passed explicitly with move semantics to prevent
         * memory errors. If you are unfamiliar with r-value references,
         * since they have no name, they pop into existence the moment they
         * are stated then pop out. This means that we do not have to worry
         * about motors continuing to hold unto.
         * If motors must be a named variable, cast it to an r-value reference
         * with std::move()
         */
        BaseQuadDrive(Drivers& drivers, Motors&& motors);

        virtual void setTargetWheelSpeeds(const QuadRPM& wheelSpeeds) override;
        virtual void initialize() override;
        virtual void update() override;
        virtual void refresh() override;
        virtual ~BaseQuadDrive() {}
    private:
        std::array<std::unique_ptr<Motor>, 4> motors_;
    };
}
#endif