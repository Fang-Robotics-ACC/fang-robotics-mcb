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
    class ICoolSerialUart
    {
    public:
        using DataHandlerRef = std::reference_wrapper<coolSerial::IDataHandler>;
        virtual void initialize() = 0;
        virtual void update() = 0;
        /**
         * HINT: DataHandlerRef{handler} where handler inherits and implements
         * IDataHandler's functions
         */
        virtual void addHandler(coolSerial::Byte dataType, DataHandlerRef handler) = 0;
        ~ICoolSerialUart() = default;
    };
    /**
     * TODO: Create a better UART interface than taproot that adapts to modm's UART
     * For testing reasons, we are using the hardcoded modm.
     * 
     * Or at least decouple the uart from taproots UartTerminalDevice
     * to allow custom ports and baudrates.
     * 
     * 921600 is the default baudrate for CV Chip
     */
    template<tap::communication::serial::Uart::UartPort kPort, int kBaudrate>
    class CoolSerialUart : public ICoolSerialUart
    {
    public:
        using HandlerMap = std::unordered_map<coolSerial::Byte, DataHandlerRef>;

        CoolSerialUart(tap::Drivers& drivers, const HandlerMap& handlerMap)
            :
            uart_{drivers.uart},
            handlerMap_{handlerMap}
        {
        }

        CoolSerialUart(tap::Drivers& drivers)
                :
                uart_{drivers.uart}
            {
            }

        void initialize() override
        {
            uart_.init<kPort, kBaudrate, tap::communication::serial::Uart::Parity::Disabled>();
        }

        void update() override
        {
            updateByteQueue();
            parser_.update();
            handleMessage();
        }

        /**
         * HINT: DataHandlerRef{handler} where handler inherits and implements
         * IDataHandler's functions
         */
        void addHandler(coolSerial::Byte dataType, DataHandlerRef handler) override
        {
            // [] needs to be able to create a default object. DataHandlerRef does not have
            // a default constructor
            handlerMap_.at(dataType) = handler;
        }
    private:

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
        tap::communication::serial::Uart& uart_;
        coolSerial::ByteQueue byteQueue_{};
        coolSerial::ContinuousParser parser_{byteQueue_};
    };
}