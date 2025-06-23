#ifndef FANG_ROBOTICS_MCB_TURRET_HEAT_LIMITER_HPP
#define FANG_ROBOTICS_MCB_TURRET_HEAT_LIMITER_HPP
#include "control/turret/data/turret_id.hpp"

#include "tap/communication/serial/ref_serial.hpp"

#include <inttypes.h>
namespace control::turret
{
    class HeatLimiter
    {
    public:
        using HeatType = uint16_t;
        using Referee = tap::communication::serial::RefSerial;

        struct Config
        {
            HeatType criticalHeatLimit;
            TurretId turretId;
        };
        /**
         * The critical heat limit triggers a full disabling
         * of the feeder motor
         */
        HeatLimiter(Referee& referee, const Config& config);

        /**
         * If the the heat exceeds the robot, recommend stop.
         *
         * If the referee system is not connected, it will NOT
         * recommend a stop.
         */
        bool stopRecommended() const;

    private:
        HeatType getTurretHeat() const;
        Referee& m_referee;
        const HeatType m_criticalHeatLimit;
        const TurretId m_turretId;
    };
}
#endif