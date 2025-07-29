#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_COMMAND_COUNTER_STRIKE_COMMAND_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_COMMAND_COUNTER_STRIKE_COMMAND_HPP
#include "field_drift_command.hpp"

#include "control/chassis/chassis_input_handler.hpp"
#include "control/chassis/chassis_subsystem.hpp"
#include "control/turret/gimbal_subsystem.hpp"

#include "wrap/rail/chassis/iholonomic_subsystem.hpp"
#include "tap/control/command.hpp"

namespace fang::chassis
{
    /**
     * First person shooter motion for holonomic drive. Plain and simple.
     * 
     * This pairs well with a mouse-supported ChassisInputHandler.
     * 
     * If you face forward, a forward input on the remote will make the robot move
     * forward. Every translation input is rotated to be relative to the turret head.
     */
    class CounterStrikeCommand : public FieldDriftCommand 
    {
    public:
        using Config = FieldDriftCommand::Config;

        /**
         * This takes a chassis subsystem and the respective inputHandler
         */
        CounterStrikeCommand
        (
            IHolonomicSubsystem& holonomicSubsystem,
            const turret::GimbalSubsystem& gimbal,
            ChassisInputHandler& inputHandler,
            const Config& config
        );

        virtual ~CounterStrikeCommand() = default;

        const char* getName() const override;
        void execute() override;

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

        static constexpr char* kName{"Counter Strike Global!"};

        const turret::GimbalSubsystem& gimbal_; //We don't want the command to alter the turret state
        const Config& kConfig_;
    };
}//namespace chassis
#endif