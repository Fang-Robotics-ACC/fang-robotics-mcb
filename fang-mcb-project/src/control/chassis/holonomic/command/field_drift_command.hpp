#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_COMMAND_FIELD_DRIFT_COMMAND_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_COMMAND_FIELD_DRIFT_COMMAND_HPP
#include "control/chassis/chassis_input_handler.hpp"
#include "control/chassis/chassis_subsystem.hpp"
#include "control/turret/gimbal_subsystem.hpp"

#include "wrap/rail/chassis/iholonomic_subsystem_control.hpp"
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
    class FieldDriftCommand : public tap::control::Command
    {
    public:
        /**
         * maxVelocity: This needs to have both components greater than
         * or equal to zero. Each component represents the maximum speed
         * each the robot will move
         *
         * maxRotation is the angular velocity that will be achieved
         * if full throttle is utilized
         */
        struct Config
        {
            physics::Velocity2D maxTranslation;
            RPM maxRotation;
        };

        /**
         * This takes a chassis subsystem and the respective inputHandler
         */
        FieldDriftCommand
        (
            IHolonomicSubsystemControl& holonomicSubsystem,
            ChassisInputHandler& inputHandler,
            const Config& config
        );

        virtual ~FieldDriftCommand() = default;

        const char* getName() const override;
        void initialize() override;
        void execute() override;
        void end(bool interrupted) override;
        bool isFinished() const;

    protected:
        /**
         * Scales input translation into tangible values
         */
        physics::Velocity2D getFieldTranslation() const;

        /**
         * Scales the rotation input on the remote into
         * a rotation where counterclockwise is positive
         */
        RPM getFieldRotation() const;

        static constexpr char* kName{"Field drift"};

        IHolonomicSubsystemControl& holonomicSubsystem_;
        ChassisInputHandler& chassisInput_;
        const Config& kConfig_;

    private:
        static void assertConfigValues(const Config& config);
        static void assertGetFieldTranslationUniformSigns
        (
            const math::AbstractVector2D& abstractFieldTranslation,
            const physics::Velocity2D& fieldTranslation
        );
    };
}//namespace chassis
#endif