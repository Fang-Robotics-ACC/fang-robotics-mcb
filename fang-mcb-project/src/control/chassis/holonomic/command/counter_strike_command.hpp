#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_COMMAND_COUNTER_STRIKE_COMMAND_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_COMMAND_COUNTER_STRIKE_COMMAND_HPP
#include "control/chassis/chassis_input_handler.hpp"
#include "control/chassis/chassis_subsystem.hpp"
#include "control/turret/gimbal_subsystem.hpp"

#include "wrap/rail/chassis/iholonomic_subsystem_control.hpp"
#include "tap/control/command.hpp"

namespace fang::chassis
{
    /**
     * This intermediates the inputs and the mecanum drive 
     */
    class CounterStrikeCommand: public tap::control::Command
    {
    public:
    struct Config
    {
        MetersPerSecond maxTranslation;
        MetersPerSecond maxXTranslation;
        MetersPerSecond maxYTranslation;
        RPM maxRotation;
        Degrees maxAngularDisplacement;
    };

        /**
         * This takes a chassis subsystem and the respective inputHandler
         */
        CounterStrikeCommand(IHolonomicSubsystemControl& chassisSubsystem, const control::turret::GimbalSubsystem& turret ,ChassisInputHandler& inputHandler, const Config& config);
        const char* getName() const override;
        void initialize() override;
        void execute() override;
        void end(bool interrupted) override;
        bool isFinished() const;
    protected:
        /**
         * Returns the fieldwise translation, translating the translation input
         * relative to the turret where forward will make the robot move
         * forwward wherever the turret is looking 
         */
        physics::Velocity2D getFieldTranslation() const;

        /**
         * Translates the rotation input on the remote into
         * a rotation where counterclockwise is positive
         */
        RPM getFieldRotation() const;

    private:
        static constexpr char* mk_name{"Chassis tank drive"};

        IHolonomicSubsystemControl& m_chassisSubsystem;
        const control::turret::GimbalSubsystem& m_gimbal; //We don't want the command to alter the turret state
        ChassisInputHandler& m_input;
        const Config& mk_config;
    };
}//namespace chassis
#endif