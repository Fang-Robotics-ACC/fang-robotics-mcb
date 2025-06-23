#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_TARDIS_KS
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_TARDIS_KS
#include "control/input_handler.hpp"
#include "control/chassis/chassis_subsystem.hpp"
#include "control/chassis/field_mecanum_command.hpp"
#include "control/chassis/algorithms/basic_downscaler.hpp"

#include "control/chassis/formulae/raziel_kalman_shredder.hpp"

#include "control/turret/gimbal_subsystem.hpp"


#include "tap/control/command.hpp"

namespace control
{
    namespace chassis
    {
        /**
         * The chassis will spin in the desired direction. It will use turret oriented strafe.
         */
        class TardisCommand: public tap::control::Command
        {
        public:
        using MotionConfig = FieldMecanumCommand::Config;
        /**
         * Positive shuriken speed is counterclockwise
         *
         * The higher the downscale coefficient, the less it will downscale with respect to speed
         */
        struct Config
        {
            RPM shurikenSpeed;
            MotionConfig motionConfig;
            double downscaleCoefficient;
            RazielKalmanShredder::Config razielKalmanShredderConfig;
        };
            /**
             * This takes a chassis subsystem and the respective inputHandler
             */
            TardisCommand(ChassisSubsystem& chassisSubsystem, const turret::GimbalSubsystem& turret ,ChassisInputHandler& input, const Config& config);
            const char* getName() const override;
            void initialize() override;
            void execute() override;
            void end(bool interrupted) override;
            bool isFinished() const;
        private:
            physics::Velocity2D calcuateFieldTranslation() const;
            static constexpr char* mk_name{"T.A.R.D.I.S. Mode"};
            ChassisSubsystem& m_chassisSubsystem;
            const turret::GimbalSubsystem& m_turret; //We don't want the command to alter the turret state
            ChassisInputHandler& m_input;
            const Config mk_config;
            const MotionConfig mk_motionConfig;
            const BasicDownscaler mk_downscaler;

            RazielKalmanShredder m_razielKalmanShredder;
        };
    }//namespace control
}//namespace chassis
#endif