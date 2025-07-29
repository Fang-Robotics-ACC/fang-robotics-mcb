#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_DRIVE_HOLONOMIC_MECANUM_SUBSYSTEM_MECANUM_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_DRIVE_HOLONOMIC_MECANUM_SUBSYSTEM_MECANUM_SUBSYSTEM_HPP

#include "driver/drivers.hpp"
#include "driver/motor/data/directionality.hpp"
#include "control/chassis/drive/holonomic/mecanum/logic/field_mecanum_logic.hpp"
#include "util/physics/data/velocity_2d.hpp"

#include "wrap/units/units_alias.hpp"


#include "wrap/trap/communication/pwm_data.hpp"
#include "wrap/trap/control/chassis/power_limiter.hpp"
#include "wrap/trap/algorithms/ramp_2d.hpp"
#include "wrap/trap/algorithms/ramp.hpp"
#include "wrap/trap/communication/sensors/imu.hpp"


#include "tap/communication/gpio/pwm.hpp"
#include "tap/control/subsystem.hpp"
#include "wrap/rail/chassis/iholonomic_subsystem.hpp"
#include "wrap/rail/chassis/iquad_drive_subsystem.hpp"

#include "driver/motor/repeat_robotics/gearbox_repeat_ultra_mk2.hpp"

namespace fang::chassis
{
    /**
     * Provides taproot friendly
     * subsystem control functionality for a mecanum drive
     * with dimensional analysis
     */
    class MecanumSubsystem : virtual public IHolonomicSubsystem
    {
    public:
        using DriveMotor = fang::motor::GearboxRepeatUltraMk2;
        using PowerLimiter = trap::control::chassis::PowerLimiter;
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
        double translationRampSpeed;
        double rotationRampSpeed;
        FieldMecanumLogic::Config mecanumLogicConfig;
        PowerLimiter::Config powerLimiterConfig;
    };

    /**
     * @param quad drive- QuadDrive to be owned by Mecanum subsystem
     * @param imu - imu attached to the chassis
     * @param config - see config
     */
    MecanumSubsystem
    (
        Drivers& drivers,
        std::unique_ptr<IQuadDriveSubsystem> quadDrive,
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

    /**
     * Called regularly
     */
    void refresh() override;

    /**
     * Kills functionality upon loss of remote input
     */
    void refreshSafeDisconnect() override;
    private:
        void updateRamps();
        void syncLogicToRamps();
        void syncWheelsToLogic();
        void updateFieldAngle();
        void setPwmFrequency();

        std::unique_ptr<IQuadDriveSubsystem> quadDrive_;
        std::unique_ptr<Imu> imu_;

        FieldMecanumLogic mecanumLogic_;
        PowerLimiter powerLimiter_;

        const double kTranslationRampSpeed_;
        const double kRotationRampSpeed_;

        trap::algorithms::Ramp2D<MetersPerSecond, Seconds> translationRamp_{{0_mps,0_mps}, kTranslationRampSpeed_};
        trap::algorithms::Ramp<RPM, Seconds> rotationRamp_{0_rpm, kRotationRampSpeed_};
    };
}//namespace fang::chassis 

#endif