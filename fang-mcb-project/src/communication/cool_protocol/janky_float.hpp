#pragma once
#include "cool_serial/byte.hpp"
#include "cool_serial/bytes.hpp"

#include <cstdint>
#include <cstring>

namespace fang::communication
{
    /**
     * This was developed to have a simple protocol to test with 
     */
    class JankyFloat
    {
    public:
        static const coolSerial::Bytes kHeaderSection;
        static coolSerial::Bytes serialize(float f)
        {
            // Bitwise hack
            // Assumes recieving and sending systems
            // Have the same bitwise type
            uint32_t binary{};

            std::memcpy(&binary, &f, sizeof(float));

            coolSerial::Bytes serialized
            {
                static_cast<coolSerial::Byte>((uint32_t) binary >> 24 & (0xff)),
                static_cast<coolSerial::Byte>((uint32_t) binary >> 16 & (0xff)),
                static_cast<coolSerial::Byte>((uint32_t) binary >>  8 & (0xff)),
                static_cast<coolSerial::Byte>((uint32_t) binary >>  0 & (0xff))
            };

            return serialized;
        }

        static float deserialize(coolSerial::Bytes bytes)
        {
      
            // Bitwise hack
            // Assumes recieving and sending systems
            // Have the same bitwise type

            uint32_t binary
            {
                (uint32_t) bytes[0] << 24
                | (uint32_t) bytes[1] << 16
                | (uint32_t) bytes[2] <<  8
                | (uint32_t) bytes[3] <<  0
            };

            // Type punning :D
            float castedBinary{};

            memcpy(&castedBinary, &binary, sizeof(float)); 
            return castedBinary;
        }
    };
}