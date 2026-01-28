#pragma
#include "cool_serial/byte_queue.hpp"

#include "i_bus_start_of_frame_search.hpp"
#include "cool_serial/dynamic_parser/dynamic_data_extract.hpp"
#include "cool_serial/dynamic_parser/data_found_listener.hpp"
#include <cool_serial/dynamic_parser/segment_found_listener.hpp>
#include <cool_serial/dynamic_parser/start_of_frame_found_listener.hpp>

namespace fang::communication 
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
class DynamicParser : public coolSerial::StartOfFrameFoundListener, public coolSerial::DataFoundListener
{
public:
    DynamicParser(coolSerial::ByteQueue& byteBuffer, DataFoundListener& listener):
        dataFoundListener_{listener},
        startOfFrameSearch_{byteBuffer, *this},
        dataExtract_ {byteBuffer, *this}
    {}
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

    class StartOfFrameSearch : public State, public IBusStartOfFrameSearch 
    {
    public:
        using IBusStartOfFrameSearch::IBusStartOfFrameSearch;
        void update() override
        {
            IBusStartOfFrameSearch::update();
        }
    };

    class DataExtract : public State, public coolSerial::DynamicDataExtract
    {
    public:
        using DynamicDataExtract::DynamicDataExtract;
        void update() override
        {
            DynamicDataExtract::update();
        }
    };

    coolSerial::DataFoundListener& dataFoundListener_;

    StartOfFrameSearch startOfFrameSearch_;
    DataExtract dataExtract_;

    std::reference_wrapper<State> state_{startOfFrameSearch_};

    // State change logic
    void startOfFrameFound() override
    {
        state_ = headerExtract_;
        // In case the buffer has more of the message
        update();
    }

    void headerFound(const HeaderData& headerData) override
    {
        if (headerData.isValid())
        {
            dataExtract_.setDataExtractionInfo(headerData.dataInfo);
            state_ = dataExtract_;
            // In case the buffer has more of the message
            update();
        }
        else
        {
            // Do not call update, wait until next cycle
            state_ = startOfFrameSearch_;
        }
    }

    void dataFound(const CoolMessageData& data) override
    {
        // Do not call update, wait until next cycle
        // at most one message is extracted every update()
        dataFoundListener_.dataFound(data);
        state_ = startOfFrameSearch_;
    }
};
}