#include "util/stl/make_vector_with_moved_list.hpp"

#include <gtest/gtest.h>
#include <memory>
#include <vector>

namespace fang::stl
{

TEST(makeVectorWithMovedList, basicMoving)
{
    std::vector<std::unique_ptr<int>>derp{
        makeVectorWithMovedList<std::unique_ptr<int>>(
            std::make_unique<int>(10),
            std::make_unique<int>(20),
            std::make_unique<int>(30)
        )
    };
}
}