#ifndef FANG_ROBOTICS_MCB_TRAP_CONTROL_CHASSIS_POWER_LIMITER_HPP
#define FANG_ROBOTICS_MCB_TRAP_CONTROL_CHASSIS_POWER_LIMITER_HPP
#include "wrap/units/units_alias.hpp"
#include "tap/communication/serial/ref_serial.hpp"
#include "rail/chassis/ipower_limiter_system.hpp"

namespace trap::control::chassis
{
    class PowerLimiter : public rail::chassis::IPowerLimiterSystem
    {
    public:
        using RefSerial = tap::communication::serial::RefSerial;
        /** @param[in] energyBufferLimitThreshold Energy in Joules. The amount of energy left in the
        *      energy buffer before power limiting is applied.
        * @param[in] energyBufferCritThreshold Energy in Joules. If the amount of energy in the energy
        *      buffer is equal or less than this value, the power limiting fraction will be 0.
        */
        struct Config
        {
            Joules startingEnergyBuffer;
            Joules energyBufferLimitThreshold;
            Joules energyBufferCritThreshold;
        };
        /**
         * Constructs a power limiter helper object.
         * @param[in] refereeSystem
         */
        PowerLimiter(const RefSerial& m_refereeSystem, const Config& config);

        /**
         * A function to be called repeatedly (in a subsystem's refresh function, for example). Checks
         * the voltage through the referee system and the current using the current sensor to calculate
         * current power consumption, which is used to update the energy buffer by integrating power.
         * Once the energy buffer is known, it is used in conjunction with the constants passed in
         * through the constructor to compute a fraction that can be used to perform power limiting.
         *
         * @note Must be called immediately *after* setpoints are configured. This function returns a
         * value between [0, 1] that you should then multiply the desired output of your motor by. See
         * class comment for more details.
         *
         * @note Tested with a normal four-wheel mecanum chassis and a two-wheel sentry chassis.
         */
        double getPowerLimitRatio() const override;

        //NOTE: Even though these are not used, the slight violation of the interface segregation
        //principle is justified as many advanced power limiters use I2C and whatnot which might
        //require manual mangement
        void initialize() override;
        void update() override;
        
    private:
        Joules getEnergyBuffer() const;

        const RefSerial& m_refereeSystem;
        const Joules m_startingEnergyBuffer;
        const Joules m_energyBufferLimitThreshold;
        const Joules m_energyBufferCritThreshold;
    };
}

#endif