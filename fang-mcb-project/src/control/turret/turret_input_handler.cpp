#include "turret_input_handler.hpp"

namespace control
{
    namespace turret
    {
        TurretInputHandler::TurretInputHandler(Remote& remote)
        :   m_remote{remote}
        {
        }
    }
}