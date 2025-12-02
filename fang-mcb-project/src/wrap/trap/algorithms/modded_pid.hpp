#pragma once

#include "smooth_pid.hpp"
#include "ipid_modder.hpp"

namespace trap::algorithms
{
/** This will require the use of units::lenth::meters instead of units::length::meter_t
 * This allows different feedfoward "modders" to change the pid output in a bundle
 */
template<typename ErrorType, typename ControlType, typename TimeUnit>
class ModdedPid : public SmoothPid<ErrorType, ControlType, TimeUnit>
{
public:
    using IModder = IPidModder<ControlType>;
    using BasePid = SmoothPid<ErrorType, ControlType, TimeUnit>;
    using Config = BasePid::Config;
    ModdedPid(
        const Config& config,
        std::unique_ptr<IModder> modder = std::make_unique<NullPidModder<ControlType>>(),
        ErrorType initialLastError = ErrorType{0.0}
    ):
        BasePid(config, initialLastError),
        modder_(std::move(modder))
    {}

    /**
     * error - how much error
     * This wrapper automatically calculates how much the error has changed
     * and the amount of time which has passed between calls
     */
    ControlType runController(ErrorType error)
    {
        return modder_->getModdedOutput(BasePid::runController(error));
    }

    /**
     * Manual delta time but with automatic derivative calculation
     */
    ControlType runController(const ErrorType& error, const TimeUnit& deltaTime)
    {
        return modder_->getModdedOutput(BasePid::runController(error, deltaTime));
    }
private:
    std::unique_ptr<IModder> modder_;
};
}