#pragma once

#include "wrap/units/units_alias.hpp"

namespace trap::algorithms
{
/**
 * Takes in the output of a pid and modifies it
 * this is useful for sprinkling in feedforward
 * to pid
 */
template<typename Control>
class IPidModder
{
public:
    /**
     * This has a null behavior so that
     */
    virtual Control getModdedOutput(const Control& output) = 0;
    virtual ~IPidModder() = default;
};

/**
 * This provides default behavior of not modifying the output at all
 */
template<typename Control>
class NullPidModder : public IPidModder<Control>
{
public:
    virtual Control getModdedOutput(const Control& output) override
    {
        return output;
    }
};
}