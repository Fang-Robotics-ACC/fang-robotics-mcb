#pragma once

#include <memory>
#include <vector>

namespace fang::stl
{
    /**
     * Due to the shenanigans of vectors and initailizer lists, it is
     * current impossible to initialize a vector of unique pointers
     * since it copies all of its elements. Thus, we do this hack :D
     */
    template<typename T>
    std::vector<T> makeUniqueVector(T uniquePointer...)
    {
        std::vector<T> uniqueVector;
        (uniqueVector.push_back(std::move(uniquePointer)), ...);
        return uniqueVector;
    }
}
