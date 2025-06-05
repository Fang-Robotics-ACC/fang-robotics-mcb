#include "flywheel_system.hpp"
#include "unitaliases.hpp"


using namespace units::literals;
namespace control
{
    namespace turret
    {
        FlywheelSystem::FlywheelSystem(Drivers& drivers, const Config& config)
        :   m_radius{config.radius / 1_rad}, m_motor{drivers, config.motorConfig}
        {
        }

        void FlywheelSystem::setTargetRimSpeed(const MetersPerSecond& rimSpeed)
        {
            m_motor.setTargetSpeed(RimSpeedToMotorSpeed(rimSpeed));
        }

        RPM FlywheelSystem::RimSpeedToMotorSpeed(const MetersPerSecond& rimSpeed) const
        {
            return rimSpeed / m_radius;
        }

        void FlywheelSystem::update()
        {
            m_motor.update();
        }
    }
}