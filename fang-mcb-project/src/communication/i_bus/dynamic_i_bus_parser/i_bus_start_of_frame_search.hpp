#pragma once
#include "communication/i_bus/i_bus.hpp"
#include "cool_serial/byte_queue.hpp"
#include "cool_serial/cool_message.hpp"
#include "cool_serial/dynamic_parser/start_of_frame_found_listener.hpp"
#include "cool_serial/dynamic_parser/segment_found_listener.hpp"
#include "cool_serial/dynamic_parser/dynamic_segment_extractor.hpp"

namespace fang::communication
{
class IBusStartOfFrameSearch
{
public:
    IBusStartOfFrameSearch(
        coolSerial::ByteQueue& queue,
        coolSerial::StartOfFrameFoundListener& listener
    ):
        queue_{queue},
        frameFoundListener_{listener}
    {
    }

    void update()
    {
    }
private:
    enum State
    {
        kSearchForFirstByte,
        kSearchForSecondByte
    };

    coolSerial::ByteQueue& queue_;
    coolSerial::StartOfFrameFoundListener& frameFoundListener_;
    State state_{kSearchForFirstByte};
};
}