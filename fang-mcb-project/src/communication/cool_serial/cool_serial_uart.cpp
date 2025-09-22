#include "cool_serial_uart.hpp"

namespace fang::communication
{
    CoolSerialUart::CoolSerialUart(tap::Drivers& drivers, const HandlerMap& handlerMap)
        :
        uart_{&drivers},
        handlerMap_{handlerMap}
    {
    }

    CoolSerialUart::CoolSerialUart(tap::Drivers& drivers)
        :
        uart_{&drivers}
    {
    }

    void CoolSerialUart::initialize()
    {
        uart_.initialize();
    }

    void CoolSerialUart::update()
    {
        updateByteQueue();
        parser_.update();
        handleMessage();
    }

    void CoolSerialUart::updateByteQueue()
    {
        // Transfer uart buffer to byte queue
        char byte{};
        while(uart_.read(byte)) 
        {
            byteQueue_.push(byte);
        }
    }

    void CoolSerialUart::referMessage(const coolSerial::CoolMessageData& message)
    {
        // [] needs to be able to create a default object. DataHandlerRef does not have
        // a default constructor
        handlerMap_.at(message.dataType).get().handleData(message.data);
    }

    void CoolSerialUart::handleMessage()
    {
        if(!parser_.currentMessageProcessed())
        {
            referMessage(parser_.getCurrentMessage());
        }
    }

    void CoolSerialUart::addHandler(coolSerial::Byte dataType, DataHandlerRef handler)
    {
        // [] needs to be able to create a default object. DataHandlerRef does not have
        // a default constructor
        handlerMap_.at(dataType) = handler;
    }
}