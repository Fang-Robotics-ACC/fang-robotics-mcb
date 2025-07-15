#include "flywheel_system.hpp"
#include "unitaliases.hpp"


using namespace units::literals;
namespace control
{
    namespace turret
    {
        FlywheelSystem::FlywheelSystem(Motor& motor, const Config& config)
        :   kRadius_{config.radius / 1_rad},
            motor_{motor}
        {
        }

        void FlywheelSystem::setTargetRimSpeed(const MetersPerSecond& rimSpeed)
        {
            targetRimSpeed_ = rimSpeed;
            motor_.setTargetSpeed(RimSpeedToMotorSpeed(rimSpeed));
        }

        MetersPerSecond FlywheelSystem::getTargetRimSpeed() const
        {
            return targetRimSpeed_;
        }

        RPM FlywheelSystem::RimSpeedToMotorSpeed(const MetersPerSecond& rimSpeed) const
        {
            return rimSpeed / kRadius_;
        }

        void FlywheelSystem::update()
        {
            motor_.update();
        }

        void FlywheelSystem::initialize()
        {
            motor_.initialize();
        }
    }
}