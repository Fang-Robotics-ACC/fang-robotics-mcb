#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_COMMAND_FIELD_DRIFT_COMMAND_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_COMMAND_FIELD_DRIFT_COMMAND_HPP
#include "control/chassis/chassis_input_handler.hpp"
#include "control/chassis/chassis_subsystem.hpp"
#include "control/turret/gimbal_subsystem.hpp"

#include "wrap/rail/chassis/iholonomic_subsystem.hpp"
#include "tap/control/command.hpp"

namespace fang::chassis
{
    /**
     * Moves the holonomic drive relative to the field.
     * The orientation of the field is generally set in the direction that
     * the robot faces on startup.
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
            IHolonomicSubsystem& holonomicSubsystem,
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

        static constexpr char* kName{"Field Drift"};

        IHolonomicSubsystem& holonomicSubsystem_;
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