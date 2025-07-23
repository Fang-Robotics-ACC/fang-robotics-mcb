#ifndef FANG_ROBOTICS_MCB_SYSTEM_ASSERT_MOST_RECENT_ASSERT_HPP
#define FANG_ROBOTICS_MCB_SYSTEM_ASSERT_MOST_RECENT_ASSERT_HPP
#include "modm/architecture/interface/assert.hpp"
namespace fang
{
    //HACK leave unitialized to be reread in debug
    extern modm::AssertionInfo gMostRecentAssert; 
}
#endif