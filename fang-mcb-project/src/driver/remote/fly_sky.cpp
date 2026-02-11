#include "fly_sky.hpp"

namespace fang::remote
{
FlySky::FlySky(Drivers& drivers, coolSerial::ByteQueue& byteQueue)
    :
    drivers_{drivers},
    ibusParser_{byteQueue, *this}
{
}

void FlySky::update()
{
    ibusParser_.update();
}
}