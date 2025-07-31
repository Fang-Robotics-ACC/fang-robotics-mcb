#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_DRIVE_HOLONOMIC_MECANUM_SUBSYSTEM_MECANUM_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_DRIVE_HOLONOMIC_MECANUM_SUBSYSTEM_MECANUM_SUBSYSTEM_HPP

#include "driver/drivers.hpp"
#include "driver/motor/data/directionality.hpp"
#include "control/chassis/drive/holonomic/mecanum/logic/field_mecanum_logic.hpp"
#include "control/chassis/drive/holonomic/holonomic_subsystem.hpp"
#include "util/physics/data/velocity_2d.hpp"

#include "wrap/units/units_alias.hpp"
#include "wrap/trap/communication/sensors/imu.hpp"
#include "wrap/rail/chassis/iquad_drive.hpp"

namespace fang::chassis
{
    /**
     * Provides taproot friendly
     * subsystem control functionality for a mecanum drive
     * with dimensional analysis
     */
    class MecanumDrive : public HolonomicSubsystem
    {
    public:
        using Imu = trap::communication::sensors::Imu;

    struct ChassisDimensionConfig
    {
        Meters wheelRadius;
        Meters verticalWheelDistance;
        Meters horizontalWheelDistance;
    };

    /**
     * Rotation Ramp Speed - how many RPM/s
     * Translation Ramp Speed - how how  many m/s/s
     * mecanumLogicConfig - see FieldMecanumLogic
     * powerLimiterConfig - see PowerLimiter
     */
    struct Config
    {
        FieldMecanumLogic::Config mecanumLogicConfig;
    };

    /**
     * @param quad drive- QuadDrive to be owned by Mecanum subsystem
     * @param imu - imu attached to the chassis
     * @param config - see config
     */
    MecanumDrive
    (
        Drivers& drivers,
        std::unique_ptr<IQuadDrive> quadDrive,
        std::unique_ptr<Imu> imu,
        const Config& config
    );

    /**
     * This is relative to the field - the axis are basically wherever the robot
     * faces forward at the start of the round
     */
    void setTargetTranslation(const physics::Velocity2D& translation) override;

    /**
     * Set the angular velocity of the chassis. Counterclockwise is positive.
     * This is due to ensuring consistency within mathematical convention. 
     * If you are taking the horizontal joystick position, you will likely need to
     * multiply it by -1.
     */
    void setTargetRotation(const RPM& rotation) override;

    void initialize() override;
    void update() override;

    /**
     * Called regularly
     */
    void refresh() override;

    /**
     * Kills functionality upon loss of remote input
     */
    void refreshSafeDisconnect() override;
    private:
        void updateSystems();
        void updateFieldAngle();
        void syncWheelsToLogic();

        std::unique_ptr<IQuadDrive> quadDrive_;
        std::unique_ptr<Imu> imu_;

        FieldMecanumLogic mecanumLogic_;
    };
}//namespace fang::chassis 

#endif