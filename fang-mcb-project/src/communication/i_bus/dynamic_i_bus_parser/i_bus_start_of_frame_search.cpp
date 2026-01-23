#include "i_bus_start_of_frame_search.hpp"
namespace fang::communication
{
void IBusStartOfFrameSearch::segmentFound(const coolSerial::Bytes& bytes)
{
    frameFoundListener_.startOfFrameFound();
}

void IBusStartOfFrameSearch::update()
{


    while(queue_.byteAvailable())
    {
        const coolSerial::Byte kNext{queue_.getNextPoppedByte()};
        if(kNext == coolSerial::CoolMessage::kStartOfFrame)
        {
            frameFoundListener_.startOfFrameFound();

            // The next bytes are likely a header
            // avoid dumping header information
            break;
        }
    }
}
}