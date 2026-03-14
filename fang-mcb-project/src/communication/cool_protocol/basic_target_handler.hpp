#pragma once

#include "ibasic_target_listener.hpp"
#include "cool_serial/idata_handler.hpp"

namespace fang::communication
{
/**
 * Initially concieved to test UART communication where the yaw of the turret can be obtained
 * from the JankyFloatHandler
 */
class BasicTargetHandler : public coolSerial::IDataHandler
{
public:
    BasicTargetHandler(IBasicTargetListener& listener);
    void handleData(const coolSerial::Bytes& bytes) override;
private:
    IBasicTargetListener& listener_;
};
}