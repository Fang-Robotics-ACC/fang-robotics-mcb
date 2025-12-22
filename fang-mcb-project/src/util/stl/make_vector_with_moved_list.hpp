#pragma once

#include "system/assert/fang_assert.hpp"
#include <iostream>
#include <memory>
#include <vector>

namespace fang::stl
{
    /**
     * Takes an arbitrary amount of arguments and moves them into a vector
     * and returns said vector.
     * 
     * Due to the shenanigans of vectors and initailizer lists, it is
     * current impossible to initialize a vector of unique pointers
     * since it copies all of its elements. Thus, we do this hack :D
     * 
     * THhs can work for anything that needs std::move()
     * 
     * This uses a feature called variadic templates.
     * 
     * Adapt from general printing to adding elements to a vector
     * https://stackoverflow.com/questions/7230621/how-can-i-iterate-over-a-packed-variadic-template-argument-list#60136761
     * 
     * T and all instances of C should be the same class
     */
    template<typename T,typename ... C >
    std::vector<T> makeVectorWithMovedList(C ... movedElement)
    {
        std::vector<T> vector{};
        // Ahh lambda function
        // Arcane fold expression magick

        // So a fold expression can cary out an operation on a pack
        // Like in math when you say 1 + 2+ ... + n
        // In this case, the lambda expression is called a lot
        // every time lambda ... lambda ... lambda ...
        // I tried refactoring the labmda out but it triggered some errors
        // so I kept it the way the post said to do.
        // the version with for-each did not work either.
        // I try to minimize odd shenanigans like this, but this greatly
        // benefits the code as we have a decent amount of variants which
        // need a vector of unique_ptr items.
        ([&]{vector.push_back(std::move(movedElement));}(), ...);
        FANG_ASSERT(vector.size() == sizeof...(movedElement), "Vector size must match parameter pack size");
        return vector;
    }
}