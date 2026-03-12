#pragma once


#include "cool_serial/byte_queue.hpp"
#include "cool_serial/continuous_parser.hpp"
#include "cool_serial/idata_handler.hpp"

#include "tap/communication/serial/uart_terminal_device.hpp"
#include "tap/drivers.hpp"

#include <functional>
#include <unordered_map>

namespace fang::communication
{
    /**
     * TODO: Create a better UART interface than taproot that adapts to modm's UART
     * For testing reasons, we are using the hardcoded modm.
     * 
     * Or at least decouple the uart from taproots UartTerminalDevice
     * to allow custom ports and baudrates.
     */
    class CoolSerialUart
    {
    public:
        using DataHandlerRef = std::reference_wrapper<coolSerial::IDataHandler>;
        using HandlerMap = std::unordered_map<coolSerial::Byte, DataHandlerRef>;

        CoolSerialUart(tap::Drivers& drivers, const HandlerMap& handlerMap, tap::communication::serial::Uart::UartPort port = tap::communication::serial::Uart::Uart1, int baudrate = 115200)
            :
            uart_{drivers.uart},
            kUartPort_{port},
            kBaudrate_{baudrate},
            handlerMap_{handlerMap}
        {
        }

        CoolSerialUart(tap::Drivers& drivers, tap::communication::serial::Uart::UartPort port = tap::communication::serial::Uart::Uart1, int baudrate = 115200)
                :
                uart_{drivers.uart},
                kBaudrate_{baudrate},
                kUartPort_{port}
            {
            }

        void initialize()
        {
            uart_.init<tap::communication::serial::Uart::Uart6, 921600, tap::communication::serial::Uart::Parity::Disabled>();
        }

        void update()
        {
            updateByteQueue();
            parser_.update();
            handleMessage();
        }

        /**
         * HINT: DataHandlerRef{handler} where handler inherits and implements
         * IDataHandler's functions
         */
        void addHandler(coolSerial::Byte dataType, DataHandlerRef handler)
        {
            // [] needs to be able to create a default object. DataHandlerRef does not have
            // a default constructor
            handlerMap_.at(dataType) = handler;
        }
    private:
        static const int kBaudRate{115200};

        void updateByteQueue()
        {
            // Transfer uart buffer to byte queue
            unsigned char byte{};
            while(uart_.read(tap::communication::serial::Uart::Uart1, &byte)) 
            {
                byteQueue_.push(byte);
            }
        }

        void handleMessage()
        {
            if(!parser_.currentMessageProcessed())
            {
                referMessage(parser_.getCurrentMessage());
            }
        }
        void referMessage(const coolSerial::CoolMessageData& message)
        {
            // [] needs to be able to create a default object. DataHandlerRef does not have
            // a default constructor
            handlerMap_.at(message.dataType).get().handleData(message.data);
        }

        HandlerMap handlerMap_{};
        const tap::communication::serial::Uart::UartPort kUartPort_;
        const int kBaudrate_;
        tap::communication::serial::Uart& uart_;
        coolSerial::ByteQueue byteQueue_{};
        coolSerial::ContinuousParser parser_{byteQueue_};
    };
}