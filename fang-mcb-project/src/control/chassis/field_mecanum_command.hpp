#ifndef FANG_ROBOTICS_MCB_FIELD_MECANUM_COMMAND_HPP
#define FANG_ROBOTICS_MCB_FIELD_MECANUM_COMMAND_HPP
#include "control/input_handler.hpp"
#include "control/chassis/chassis_subsystem.hpp"

#include "tap/control/command.hpp"

namespace control
{
    namespace chassis
    {
        /**
         * This intermediates the inputs and the mecanum drive 
         */
        class FieldMecanumCommand: public tap::control::Command
        {
            /**
             * This takes a chassis subsystem and the respective inputHandler
             */
            FieldMecanumCommand(ChassisSubsystem& chassisSubsystem, InputHandler& inputHandler);
            const char* getName() const override;
            void initialize() override;
            void execute() override;
            void end(bool interrupted) override;
            bool isFinished() const;
        private:
            static constexpr char* mk_name{"Chassis tank drive"};
            ChassisSubsystem& m_chassisSubsystem;
            InputHandler& m_inputHandler;
        };
    }//namespace control
}//namespace chassis
#endif