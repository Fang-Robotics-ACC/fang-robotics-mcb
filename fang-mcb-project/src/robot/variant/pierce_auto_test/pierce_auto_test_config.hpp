#pragma once
#include "pierce_auto_test.hpp"
namespace fang::robot 
{
/**
 * Prevent's static initialization fiasco
 * https://isocpp.org/wiki/faq/ctors#static-init-order-on-first-use
 */
const PierceAutoTest::Config& getPierceAutoTestConfig();
}