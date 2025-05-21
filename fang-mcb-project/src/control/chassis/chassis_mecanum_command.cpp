#include "chassis_mecanum_command.hpp"
namespace control
{
    namespace chassis
    {
        ChassisMecanumCommand::ChassisMecanumCommand(ChassisSubsystem& chassisSubsystem, InputHandler& inputHandler)
        : m_chassisSubsystem{chassisSubsystem}, m_inputHandler{inputHandler}
        {}

        const char* ChassisMecanumCommand::getName() const
        {
            return mk_name;
        }

        void ChassisMecanumCommand::initialize()
        {}

        void ChassisMecanumCommand::execute()
        {}

        void ChassisMecanumCommand::end(bool interrupted)
        {}

        bool ChassisMecanumCommand::isFinished() const
        {}
    }//namespace control
}//namespace chassis