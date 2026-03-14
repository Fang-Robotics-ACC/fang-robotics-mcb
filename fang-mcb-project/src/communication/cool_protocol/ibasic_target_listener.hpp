#pragma once
#include "system/assert/fang_assert.hpp"
#include "echo/basic_target_generated.h"
namespace fang::communication
{
class IBasicTargetListener
{
public:
    virtual void basicTargetFound(const BasicTargetT& basicTarget) = 0;
    ~IBasicTargetListener() = default;
};

class NullBasicTargetListener : public IBasicTargetListener
{
public:
    void basicTargetFound(const BasicTargetT& basicTarget) override
    {
        FANG_ASSERT(false, "yeah");
        static BasicTargetT target{basicTarget};
    }
};
}