#ifndef FANG_ROBOTICS_MCB_MOTOR_DATA_DIRECTIONALITY_HPP
#define FANG_ROBOTICS_MCB_MOTOR_DATA_DIRECTIONALITY_HPP
#include <cstdint>

namespace motor
{
    //This uint8_t is used because there shouldn't be more than 256 values of motor directionality
    //Honestly consider refactoring if it goes past 25.
    enum class Directionality : std::uint8_t
    {
        BIDIRECTIONAL,
        UNIDIRECTIONAL
    };
}
#endif