#pragma once
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
        static BasicTargetT target{basicTarget};
    }
};
}