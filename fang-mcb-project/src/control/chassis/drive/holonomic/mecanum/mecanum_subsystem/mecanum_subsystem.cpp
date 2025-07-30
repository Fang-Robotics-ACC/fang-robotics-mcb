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
        Subsystem{&drivers},
        //Owned systems
        quadDrive_{std::move(quadDrive_)},
        imu_{std::move(imu)},
        //Static Utils
        mecanumLogic_{config.mecanumLogicConfig},
        //RampSpeed
        kTranslationRampSpeed_{config.translationRampSpeed},
        kRotationRampSpeed_{config.rotationRampSpeed}
    {
    }


    void MecanumSubsystem::setTargetTranslation(const physics::Velocity2D& translation)
    {
        translationRamp_.setTarget(translation);
    }

    void MecanumSubsystem::setTargetRotation(const RPM& rotation)
    {

        rotationRamp_.setTarget(rotation);
    }

    void MecanumSubsystem::initialize()
    {
        quadDrive_->initialize();
    }

    void MecanumSubsystem::refresh()
    {
        updateRamps();
        syncLogicToRamps();
        syncWheelsToLogic();
        updateFieldAngle();
    }

    void MecanumSubsystem::refreshSafeDisconnect()
    {
        //The robot should not move when disconnected
        mecanumLogic_.setTranslation({0_mps, 0_mps});
        mecanumLogic_.setRotation(0_rpm);
        //Make sure wheels are sent a zero signal
        syncWheelsToLogic();
    }

    void MecanumSubsystem::updateRamps()
    {
        translationRamp_.update();
        rotationRamp_.update();
    }

    void MecanumSubsystem::syncLogicToRamps()
    {
        mecanumLogic_.setTranslation(translationRamp_.getValue());
        mecanumLogic_.setRotation(rotationRamp_.getValue());
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