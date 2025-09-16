#include "cool_serial_uart.hpp"

namespace fang::communication
{
    CoolSerialUart::CoolSerialUart(Drivers& drivers, HandlerMap& handlerMap)
        :
        uart_{&drivers},
        handlerMap_{handlerMap}
    {
    }

    CoolSerialUart::CoolSerialUart(Drivers& drivers)
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
        if(uart_.read(byte)) 
        {
            byteQueue_.push(byte);
        }
    }

    void CoolSerialUart::referMessage(const coolSerial::CoolMessageData& message)
    {
        handlerMap_[message.dataType].get().handleData(message.data);
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
        handlerMap_[dataType] = handler;

    }
}