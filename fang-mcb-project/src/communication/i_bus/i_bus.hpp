#include "communication/uart/byte.hpp"

#include <array>
#include <cstdint>

#pragma once
/**
 * https://basejunction.wordpress.com/2015/08/23/en-flysky-i6-14-channels-part1/
 * 
 * This provides C++ information for the iBus 
 */

namespace fang::communication::ibus
{
static constexpr Byte kFirstStartOfFrame{0x20};
static constexpr Byte kSecondStartofFrame{0x40};
static constexpr std::array<Byte, 2> kStartOfFrame{kFirstStartOfFrame, kSecondStartofFrame};

static constexpr int kChannelCount{14};

static constexpr int kStartOfFrameSize{2}; // Bytes
static constexpr int kBytesPer16BitInt{2};
static constexpr int kChecksumSectionSize{2}; // Bytes

static constexpr int kChannelSectionSize{kChannelCount * kBytesPer16BitInt}; // Bytes (Channel + 16 bit Checkshum)
static constexpr int kPacketSize{kStartOfFrameSize + kChannelSectionSize + kChecksumSectionSize}; // Bytes

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
}