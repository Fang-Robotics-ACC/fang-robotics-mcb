#include "echo/basic_target_generated.h"
namespace fang::communication
{
class IBasicTargetListener
{
public:
    virtual void basicTargetFound(const BasicTarget& basicTarget) = 0;
    ~IBasicTargetListener() = default;
};
}