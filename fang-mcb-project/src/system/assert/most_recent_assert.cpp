#include "most_recent_assert.hpp"
namespace fang
{
    //HACK leave uninitialized to read data from RAM
    modm::AssertionInfo gMostRecentAssert; 
}