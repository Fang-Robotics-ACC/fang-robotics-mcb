#include "flywheel_system.hpp"
#include "wrap/units/units_alias.hpp"

using namespace units::literals;
namespace fang::turret
{
    OldFlywheelSystem::OldFlywheelSystem(Drivers& drivers, const Config& config)
    :   m_radius{config.radius / 1_rad},
        m_motor{drivers, config.motorConfig}
    {
    }

    void OldFlywheelSystem::setTargetRimSpeed(const MetersPerSecond& rimSpeed)
    {
        m_motor.setTargetSpeed(RimSpeedToMotorSpeed(rimSpeed));
    }

    RPM OldFlywheelSystem::RimSpeedToMotorSpeed(const MetersPerSecond& rimSpeed) const
    {
        return rimSpeed / m_radius;
    }

    void OldFlywheelSystem::update()
    {
        m_motor.update();
    }

    void OldFlywheelSystem::initialize()
    {
        m_motor.initialize();
    }
}