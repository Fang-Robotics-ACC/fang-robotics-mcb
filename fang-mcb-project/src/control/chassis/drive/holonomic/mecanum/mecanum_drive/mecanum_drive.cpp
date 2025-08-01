#include "mecanum_drive.hpp"

#include "system/assert/fang_assert.hpp"
#include "tap/algorithms/math_user_utils.hpp"
#include "wrap/units/units_alias.hpp"


namespace fang::chassis
{
    MecanumDrive::MecanumDrive
    (
        Drivers& drivers,
        std::unique_ptr<IQuadDrive> quadDrive,
        std::unique_ptr<Imu> imu,
        const Config& config
    ):
        //Base
        HolonomicSubsystem{drivers},
        quadDrive_{std::move(quadDrive)},
        imu_{std::move(imu)},
        mecanumLogic_{config.mecanumLogicConfig}
    {
    }

    void MecanumDrive::setTargetTranslation(const physics::Velocity2D& translation)
    {
        mecanumLogic_.setTranslation(translation);
    }

    void MecanumDrive::setTargetRotation(const RPM& rotation)
    {
        mecanumLogic_.setRotation(rotation);
    }

    void MecanumDrive::initialize()
    {
        quadDrive_->initialize();
    }

    void MecanumDrive::update()
    {
        updateSystems();
        updateFieldAngle();
        syncWheelsToLogic();
    }

    void MecanumDrive::refresh()
    {
        update();
    }

    void MecanumDrive::refreshSafeDisconnect()
    {
        //The robot should not move when disconnected
        mecanumLogic_.setTranslation({0_mps, 0_mps});
        mecanumLogic_.setRotation(0_rpm);
        //Make sure wheels are sent a zero signal
        syncWheelsToLogic();
    }

    void MecanumDrive::updateSystems()
    {
        quadDrive_->update();
    }

    void MecanumDrive::syncWheelsToLogic()
    {
        quadDrive_->setTargetWheelSpeeds(mecanumLogic_.getWheelSpeeds());
    }

    void MecanumDrive::updateFieldAngle()
    {
        const Radians currentFieldAngle{imu_->getYaw()};
        mecanumLogic_.setRobotAngle(currentFieldAngle);
    }
}//namespace chassis