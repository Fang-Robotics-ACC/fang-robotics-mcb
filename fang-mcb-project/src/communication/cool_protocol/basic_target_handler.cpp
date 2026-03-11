#include "basic_target_handler.hpp"
#include "cool_serial/idata_handler.hpp"
#include "echo/basic_target_generated.h" 

namespace fang::communication
{
/**
 * Initially concieved to test UART communication where the yaw of the turret can be obtained
 * from the JankyFloatHandler
 */

BasicTargetHandler::BasicTargetHandler(IBasicTargetListener& listener) : listener_{listener}
{
}

void BasicTargetHandler::handleData(const coolSerial::Bytes& bytes)
{
    BasicTargetT basicTarget{};
    GetBasicTarget(bytes.data())->UnPackTo(&basicTarget);
    listener_.basicTargetFound(basicTarget);
}
}