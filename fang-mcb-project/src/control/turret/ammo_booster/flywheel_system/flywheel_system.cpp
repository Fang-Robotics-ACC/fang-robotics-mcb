#include "flywheel_system.hpp"
#include "wrap/units/units_alias.hpp"

using namespace units::literals;
namespace fang::turret
{
    FlywheelSystem::FlywheelSystem(Motor motor, const Config& config)
    :   kRadius_{config.radius / 1_rad},
        motor_{std::move(motor)}
    {
    }

    void FlywheelSystem::setTargetRimSpeed(const MetersPerSecond& rimSpeed)
    {
        targetRimSpeed_ = rimSpeed;
        motor_->setTargetSpeed(RimSpeedToMotorSpeed(rimSpeed));
    }

    RPM FlywheelSystem::RimSpeedToMotorSpeed(const MetersPerSecond& rimSpeed) const
    {
        return rimSpeed / kRadius_;
    }

    void FlywheelSystem::update()
    {
        motor_->update();
    }

    void FlywheelSystem::initialize()
    {
        motor_->initialize();
    }
}