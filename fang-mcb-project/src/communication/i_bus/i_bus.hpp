#include "communication/uart/byte.hpp"
#include <cstdint>

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

    static constexpr int kStartOfFrameSize{2}; // Bytes
    static constexpr int kChannelSectionSize{30}; // Bytes (Channel + 16 bit Checkshum)
    static constexpr int kPacketSize{32}; // Bytes

    static constexpr uint16_t kChecksumConstant{0xffff};

    // Unlike UMN, the start of frame and end of frame are not stored in the buffer
    static constexpr uint16_t kInitialCheksum{kFirstStartOfFrame + kSecondStartofFrame};

    /**
     * The checksum is calculated by taking bytes 0-30 and adding them together.
     * The sum is subtracted from the checksum constant.
     * 
     * If the packet is valid, bytes 31 (most significant byte) and 32 (least significant) 
     * will be the same as the calculated checksum
     */
    // https://github.com/mokhwasomssi/stm32_hal_ibus/blob/main/ibus.c
};
}