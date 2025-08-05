#include "basic_flywheel.hpp"
#include "wrap/units/units_alias.hpp"

using namespace units::literals;
namespace fang::turret
{
    BasicFlywheel::BasicFlywheel(std::unique_ptr<Motor> motor, const Config& config)
    :   kRadius_{config.radius / 1_rad},
        motor_{std::move(motor)}
    {
    }

    void BasicFlywheel::setTargetRimSpeed(const MetersPerSecond& rimSpeed)
    {
        targetRimSpeed_ = rimSpeed;
        motor_->setTargetSpeed(RimSpeedToMotorSpeed(rimSpeed));
    }

    RPM BasicFlywheel::RimSpeedToMotorSpeed(const MetersPerSecond& rimSpeed) const
    {
        return rimSpeed / kRadius_;
    }

    void BasicFlywheel::update()
    {
        motor_->update();
    }

    void BasicFlywheel::initialize()
    {
        motor_->initialize();
    }
}