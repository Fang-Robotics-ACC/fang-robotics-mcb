#include "field_mecanum_command.hpp"
#include "chassislogicaliases.hpp"
#include "unitaliases.hpp"
namespace control
{
    namespace chassis
    {
        FieldMecanumCommand::FieldMecanumCommand(ChassisSubsystem& chassisSubsystem, InputHandler& inputHandler)
        : m_chassisSubsystem{chassisSubsystem}, m_inputHandler{inputHandler}
        {}

        const char* FieldMecanumCommand::getName() const
        {
            return mk_name;
        }

        void FieldMecanumCommand::initialize()
        {

        }

        void FieldMecanumCommand::execute()
        {
            const logic::chassis::Velocity2D translation{m_inputHandler.getChassisInputs().getRemoteTranslation()};
            const RPM rotation{m_inputHandler.getChassisInputs().getRemoteRotation()};
            m_chassisSubsystem.setMotion(translation, rotation);
        }

        void FieldMecanumCommand::end(bool interrupted)
        {}

        bool FieldMecanumCommand::isFinished() const
        {}
    }//namespace control
}//namespace chassis