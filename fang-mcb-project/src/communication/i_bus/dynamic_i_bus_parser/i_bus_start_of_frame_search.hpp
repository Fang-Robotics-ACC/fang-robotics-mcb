#pragma once
#include "communication/i_bus/i_bus.hpp"
#include "cool_serial/byte_queue.hpp"
#include "cool_serial/cool_message.hpp"
#include "cool_serial/dynamic_parser/start_of_frame_found_listener.hpp"
#include "cool_serial/dynamic_parser/segment_found_listener.hpp"
#include "cool_serial/dynamic_parser/dynamic_segment_extractor.hpp"

namespace fang::communication
{
class IBusStartOfFrameSearch  : coolSerial::SegmentFoundListener
{
public:
    IBusStartOfFrameSearch(
        coolSerial::ByteQueue& queue,
        coolSerial::StartOfFrameFoundListener& listener
    ):
        queue_{queue},
        segmentExtractor_{queue, *this, IBus::kStartOfFrameSize},
        frameFoundListener_{listener}
    {
    }
    void segmentFound(const coolSerial::Bytes& bytes) override;

    void update()
    {
    }
private:
    coolSerial::ByteQueue& queue_;
    coolSerial::DynamicSegmentExtractor segmentExtractor_;
    coolSerial::StartOfFrameFoundListener& frameFoundListener_;
};
}