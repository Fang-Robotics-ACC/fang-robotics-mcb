#pragma once

#include "janky_float.hpp"
#include "cool_serial/idata_handler.hpp"

namespace fang::communication
{
    /**
     * Initially concieved to test UART communication where the yaw of the turret can be obtained
     * from the JankyFloatHandler
     */
    class JankyFloatHandler : public coolSerial::IDataHandler
    {
    public:
        void handleData(const coolSerial::Bytes& bytes) override;

        float getCurrentFloat();
    private:
        float currentFloat_{};
    };
}