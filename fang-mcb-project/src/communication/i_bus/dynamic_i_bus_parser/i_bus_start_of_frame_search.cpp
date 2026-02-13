#include "i_bus_start_of_frame_search.hpp"
namespace fang::communication::ibus
{
void StartOfFrameSearch::update()
{
    while(queue_.byteAvailable())
    {
        const coolSerial::Byte kNext{queue_.getNextPoppedByte()};
        switch(state_)
        {
        case kSearchForFirstByte:
            if(kNext == kFirstStartOfFrame)
            {
                state_ = kSearchForSecondByte;
            }
            break;
        case kSearchForSecondByte:
            if(kNext == kSecondStartofFrame)
            {
                frameFoundListener_.startOfFrameFound();
            }
            // Either way, the first SOF will be sought ought because
            // if it is invalid, the process restarts
            // if it is valid, then process restarts
            // when the process restarts, then the state is kSearchForFirstByte
            state_ = kSearchForFirstByte;
        }
    }
}
}