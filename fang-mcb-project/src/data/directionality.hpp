#ifndef DIRECTIONALITY_HPP_SDFEFEF_YEET
#define DIRECTIONALITY_HPP_SDFEFEF_YEET
#include <cstdint>

namespace data
{
    namespace motors
    {
        //This uint8_t is used because there shouldn't be more than 256 values of motor directionality
        //Honestly consider refactoring if it goes past 25.
        enum class Directionality : std::uint8_t
        {
            BIDIRECTIONAL,
            UNIDIRECTIONAL
        };
    }
}
#endif