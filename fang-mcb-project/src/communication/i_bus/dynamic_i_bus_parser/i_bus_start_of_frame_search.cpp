#include "i_bus_start_of_frame_search.hpp"
namespace fang::communication
{
void IBusStartOfFrameSearch::update()
{
    while(queue_.byteAvailable())
    {
        const coolSerial::Byte kNext{queue_.getNextPoppedByte()};
        switch(state_)
        {
        case kSearchForFirstByte:
            state_ = kSearchForSecondByte;
            break;
        case kSearchForSecondByte:
            frameFoundListener_.startOfFrameFound();
            state_ = kSearchForFirstByte;
        }
    }
}
}