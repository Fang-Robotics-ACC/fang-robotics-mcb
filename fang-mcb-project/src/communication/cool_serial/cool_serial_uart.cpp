#include "cool_serial_uart.hpp"

namespace fang::communication
{
    CoolSerialUart::CoolSerialUart(tap::Drivers& drivers, const HandlerMap& handlerMap, tap::communication::serial::Uart::UartPort port, int baudrate)
        :
        uart_{drivers.uart},
        kUartPort_{port},
        kBaudrate_{baudrate},
        handlerMap_{handlerMap}
    {
    }

    CoolSerialUart::CoolSerialUart(tap::Drivers& drivers, tap::communication::serial::Uart::UartPort port, int baudrate)
        :
        uart_{drivers.uart},
        kBaudrate_{baudrate},
        kUartPort_{port}
    {
    }

    void CoolSerialUart::initialize()
    {
        uart_.init<tap::communication::serial::Uart::Uart6, 921600, tap::communication::serial::Uart::Parity::Disabled>();
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
        unsigned char byte{};
        while(uart_.read(kUartPort_, &byte)) 
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