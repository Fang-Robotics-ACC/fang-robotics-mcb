#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_COMMAND_TARDIS_COMMAND_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_COMMAND_TARDIS_COMMAND_HPP
#include "shuriken_command.hpp"
#include "control/chassis/chassis_subsystem.hpp"
#include "control/chassis/algorithms/basic_downscaler.hpp"

#include "control/chassis/formulae/raziel_kalman_shredder.hpp"

#include "control/turret/gimbal_subsystem.hpp"

#include "util/chrono/simple_timer.hpp"


#include "tap/control/command.hpp"

namespace fang::chassis 
{
    /**
     * The chassis will spin in the desired direction. It will use turret oriented strafe.
     */
    class TardisCommand : public ShurikenCommand
    {
    public:
    using MotionConfig = CounterStrikeCommand::Config;
    /**
     * Positive shuriken speed is counterclockwise
     *
     * The higher the downscale coefficient, the less it will downscale with respect to speed
     */
    struct Config
    {
        physics::Velocity2D maxTranslation;
        RPM maxRotation;
        double downscaleCoefficient;
        RazielKalmanShredder::Config razielKalmanShredderConfig;
    };
        /**
         * This takes a chassis subsystem and the respective inputHandler
         */
        TardisCommand(IHolonomicSubsystemControl& chassisSubsystem, const control::turret::GimbalSubsystem& turret ,ChassisInputHandler& input, const Config& config);
        const char* getName() const override;
        void execute() override;
    protected:
        RPM getFieldRotation() const;
    private:
        static constexpr char* mk_name{"T.A.R.D.I.S. Mode"};
        const Config mk_config;
        RazielKalmanShredder m_razielKalmanShredder;
        chrono::SimpleTimer m_kalmanTimer{}; //To provide an input for the Raziel-Kalman Shredder
    };
}
#endif