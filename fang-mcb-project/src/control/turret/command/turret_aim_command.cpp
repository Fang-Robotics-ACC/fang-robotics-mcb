#include "control/turret/command/turret_aim_command.hpp"

namespace control
{
    namespace turret
    {
        TurretAimCommand::TurretAimCommand(TurretSubsystem& turret, TurretInputHandler& input, const config::motion::TurretConfig& motionConfig)
        :   m_turret{turret}, m_input{input}, mk_motionConfig{motionConfig}
        {
        }

        const char* TurretAimCommand::getName() const
        {
            return mk_name;
        }

        void TurretAimCommand::initialize()
        {
        }

        void TurretAimCommand::execute()
        {
        }

        void TurretAimCommand::end(bool interrupted)
        {
        }

        bool TurretAimCommand::isFinished() const
        {
            //This is meant to be a default command
            return false;
        }

        void TurretAimCommand::setPitchSpeed(const Seconds& delta)
        {
        }

        void TurretAimCommand::setYawSpeed(const Seconds& delta)
        {
        }

        Radians TurretAimCommand::rpmToDisplacement(const RPM& speed, const Seconds& time) const
        {
            return speed * time;
        }
    }
}