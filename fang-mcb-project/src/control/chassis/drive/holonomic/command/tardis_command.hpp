#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_COMMAND_TARDIS_COMMAND_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_COMMAND_TARDIS_COMMAND_HPP

#include "shuriken_command.hpp"

#include "control/chassis/algorithms/basic_downscaler.hpp"
#include "control/chassis/formulae/azriel_shredder.hpp"
#include "control/turret/gimbal/field_gimbal_subsystem.hpp"
#include "util/chrono/simple_timer.hpp"

#include "tap/control/command.hpp"

namespace fang::chassis 
{
    /**
     * This utilizes the Raziel Shredder, an family of anti-Kalman algorithms
     * designed to induce a bias which is infinitely differentiable i.e. everything up to
     * acceleratino is under constant change which makes linear prediction more difficult.
     * 
     * It does not randomize spin since Kalman Filters do overcome them.
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
        AzrielShredder::Config razielKalmanShredderConfig;
    };
        /**
         * This takes a chassis subsystem and the respective inputHandler
         */
        TardisCommand
        (
            HolonomicSubsystem& chassisSubsystem,
            const turret::FieldGimbalSubsystem& turret,
            ChassisInputHandler& input,
            const Config& config
        );
        const char* getName() const override;
        void execute() override;
    protected:
        RPM getFieldRotation(const physics::Velocity2D& targetFieldTranslation) const;
    private:
        static constexpr char* kName{"T.A.R.D.I.S. Mode"};

        const Config kConfig_;
        AzrielShredder razielKalmanShredder_;
        chrono::SimpleTimer kShredderTimer{}; //To provide an input for the Raziel-Kalman Shredder
    };
}
#endif