#pragma once

#include "driver/drivers.hpp"

#include "cool_serial/byte_queue.hpp"
#include "cool_serial/continuous_parser.hpp"
#include "cool_serial/idata_handler.hpp"

#include "tap/communication/serial/uart_terminal_device.hpp"

#include <functional>
#include <unordered_map>

namespace fang::communication
{
    using DataHandlerRef = std::reference_wrapper<coolSerial::IDataHandler>;
    using HandlerMap = std::unordered_map<coolSerial::Byte, DataHandlerRef>;
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
        CoolSerialUart(Drivers& drivers);
        CoolSerialUart(Drivers& drivers, HandlerMap& handlerMap);

        void initialize();
        void update();
        /**
         * HINT: DataHandlerRef{handler} where handler inherits and implements
         * IDataHandler's functions
         */
        void addHandler(coolSerial::Byte dataType, DataHandlerRef handler);
    private:
        static const int kBaudRate{115200};
        void updateByteQueue();
        void handleMessage();
        void referMessage(const coolSerial::CoolMessageData& message);

        HandlerMap handlerMap_{};
        tap::communication::serial::UartTerminalDevice uart_;
        coolSerial::ByteQueue byteQueue_{};
        coolSerial::ContinuousParser parser_{byteQueue_};
    };
}