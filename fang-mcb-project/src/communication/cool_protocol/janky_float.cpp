#include "janky_float.hpp"

namespace fang::communication
{
    const coolSerial::Bytes JankyFloat::kHeaderSection{0x89, 0x0, 0x4, 0xff, 0xa7};
}