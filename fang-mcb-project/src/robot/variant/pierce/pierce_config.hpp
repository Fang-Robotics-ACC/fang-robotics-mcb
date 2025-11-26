#pragma once
#include "pierce.hpp"
namespace fang::robot 
{
    /**
     * Prevent's static initialization fiasco
     * https://isocpp.org/wiki/faq/ctors#static-init-order-on-first-use
     */
    const Pierce::Config& getPierceConfig();
}