#include "mecanum_subsystem.hpp"

#include "system/assert/fang_assert.hpp"
#include "tap/algorithms/math_user_utils.hpp"
#include "wrap/units/units_alias.hpp"


namespace fang::chassis
{
    MecanumSubsystem::MecanumSubsystem
    (
        Drivers& drivers,
        std::unique_ptr<IQuadDriveSubsystem> quadDrive,
        std::unique_ptr<Imu> imu,
        const Config& config
    ):
        //Base
        HolonomicSubsystem{drivers},
        quadDrive_{std::move(quadDrive_)},
        imu_{std::move(imu)},
        mecanumLogic_{config.mecanumLogicConfig}
    {
    }

    void MecanumSubsystem::setTargetTranslation(const physics::Velocity2D& translation)
    {
        mecanumLogic_.setTranslation(translation);
    }

    void MecanumSubsystem::setTargetRotation(const RPM& rotation)
    {
        mecanumLogic_.setRotation(rotation);
    }

    void MecanumSubsystem::initialize()
    {
        quadDrive_->initialize();
    }

    void MecanumSubsystem::refresh()
    {
        updateFieldAngle();
        syncWheelsToLogic();
    }

    void MecanumSubsystem::refreshSafeDisconnect()
    {
        //The robot should not move when disconnected
        mecanumLogic_.setTranslation({0_mps, 0_mps});
        mecanumLogic_.setRotation(0_rpm);
        //Make sure wheels are sent a zero signal
        syncWheelsToLogic();
    }

    void MecanumSubsystem::syncWheelsToLogic()
    {
        quadDrive_->setTargetWheelSpeeds(mecanumLogic_.getWheelSpeeds());
    }

    void MecanumSubsystem::updateFieldAngle()
    {
        const Radians currentFieldAngle{imu_->getYaw()};
        mecanumLogic_.setRobotAngle(currentFieldAngle);
    }
}//namespace chassis