#include "communication/uart/byte.hpp"

#pragma once
/**
 * https://basejunction.wordpress.com/2015/08/23/en-flysky-i6-14-channels-part1/
 * 
 * This provides C++ information for the iBus 
 */

namespace fang::communication
{

class IBus
{
public:
    static constexpr Byte kFirstStartOfFrame{0x20};
    static constexpr Byte kSecondStartofFrame{0x40};
private:
};
}