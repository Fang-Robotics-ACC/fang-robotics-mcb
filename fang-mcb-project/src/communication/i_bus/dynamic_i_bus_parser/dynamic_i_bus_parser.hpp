#pragma
#include "cool_serial/byte_queue.hpp"

#include "i_bus_start_of_frame_search.hpp"
#include "cool_serial/dynamic_parser/dynamic_segment_extractor.hpp"

namespace fang::communication::ibus
{
/**
 * Adaptation of coolSerial dynamic parser for flysky
 * 
 * It searches for the 2 byte SOF, it will keep dumping the queue until it finds the SOF section
 * 
 * Upon finding the SOF, it extracts a segment of 30 bytes which include both the channel section (28 bytes) and the
 * checksum (2 bytes)
 * 
 * If the channel data is valid, it informs a ChannelFoundListener with the channel data.
 */
class DynamicParser : public coolSerial::StartOfFrameFoundListener, public coolSerial::SegmentFoundListener
{
public:
    DynamicParser(coolSerial::ByteQueue& byteBuffer);

    void update()
    {
        state_.get().update();
    }
private:
     /**
      * Allows other classes to mesh in
      */
    class State
    {
    public:
        virtual void update() = 0;
    };

    class StartOfFrameSearch : public State, public ibus::StartOfFrameSearch 
    {
    public:
        using ibus::StartOfFrameSearch::StartOfFrameSearch;
        void update() override
        {
            StartOfFrameSearch::update();
        }
    };

    class SegmentExtract : public State, public coolSerial::DynamicSegmentExtractor
    {
    public:
        using DynamicSegmentExtractor::DynamicSegmentExtractor;
        void update() override
        {
            DynamicSegmentExtractor::update();
        }
    };

    StartOfFrameSearch startOfFrameSearch_;
    // This extracts both the channel data and the associated checksum
    coolSerial::DynamicSegmentExtractor segmentExtract_;

    std::reference_wrapper<State> state_{startOfFrameSearch_};

    // State change logic
    void startOfFrameFound() override;
    void segmentFound(const coolSerial::Bytes& bytes) override;
};
}