#include "control/turret/command/aim_command.hpp"

namespace control
{
    namespace turret
    {
        using namespace units::literals;
        AimCommand::AimCommand(TurretSubsystem& turret, TurretInputHandler& input, const config::motion::TurretMotionConfig& motionConfig)
        :   m_turret{turret},
            m_input{input},
            mk_motionConfig{motionConfig}

        {
            addSubsystemRequirement(&m_turret);
        }

        void AimCommand::initialize()
        {
        }

        void AimCommand::execute()
        {
            const Seconds delta{m_executeTimer.getDurationAndReset()};
            setPitch(delta);
        }

        void AimCommand::end(bool interrupted)
        {
        }

        bool AimCommand::isFinished() const
        {
            //Default command must never finish
            return false;
        }

        void AimCommand::setPitch(const Microseconds& delta)
        {
            const double k_pitchScaler{m_input.getPitch()};
            m_turret.setPitch(k_pitchScaler * 20_deg);
        }
    }
}