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
        /**
         * Returns the msb bytes
         */
        static coolSerial::Bytes serialize(float f);
        /**
         * Returns the associated float
         */
        static float deserialize(coolSerial::Bytes bytes);
    };
}