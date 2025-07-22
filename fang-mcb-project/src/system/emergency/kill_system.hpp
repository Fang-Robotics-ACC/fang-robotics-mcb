#ifndef FANG_ROBOTICS_MCB_SYSTEM_EMERGENCY_KILL_SYSTEM_HPP
#define FANG_ROBOTICS_MCB_SYSTEM_EMERGENCY_KILL_SYSTEM_HPP
namespace fang::emergency
{
    /**
     * Hardcoded dirty static function to prevent the robot
     * from doing ANYTHING.
     * 
     * If it is possible to cut power, it should be called here
     * Usually, this is only called in modm_abandon upon an assertion
     * error.
     * 
     * However, it can be useful to have a killswitch mapping (potentially)
     * 
     * WARNING: This will require a power cycle to exit.
     * 
     * @post The robot will be unable to move. It may send only error signals
     * 
     * This is hardcoded as static function with intent as a system-wide shutdown
     * Including all drivers if possible
     */
    void killSystem();
}
#endif