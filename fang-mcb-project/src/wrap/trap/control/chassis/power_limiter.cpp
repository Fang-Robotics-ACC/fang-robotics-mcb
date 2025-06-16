#include "power_limiter.hpp"
#include "unitaliases.hpp"
#include "tap/communication/serial/ref_serial.hpp"
#include "tap/algorithms/math_user_utils.hpp"
namespace trap::control::chassis
{
    PowerLimiter::PowerLimiter(const RefSerial& refereeSystem, const Config& config)
    :   m_refereeSystem{refereeSystem},
        m_startingEnergyBuffer{config.startingEnergyBuffer},
        m_energyBufferLimitThreshold{config.energyBufferLimitThreshold},
        m_energyBufferCritThreshold{config.energyBufferCritThreshold}
    {
    }

    float PowerLimiter::getPowerLimitRatio()
    {

        const bool refereeConnected{m_refereeSystem.getRefSerialReceivingData()};
        //Guard clause, should not shut down the chassis if there is no referee system to allow testing
        if (!refereeConnected)
        {
            return 1.0f;
        }

        const Joules energyBuffer{getEnergyBuffer()};

        //Optimization so we don't calculate this unless we have to
        if (energyBuffer < m_energyBufferLimitThreshold)
        {
            // If we have eaten through the majority of our energy buffer, do harsher limiting
            // Cap the penalty at energyBufferCritThreshold / energyBufferLimitThreshold.

            const Joules remainingEnergy{energyBuffer - m_energyBufferCritThreshold};
            //Let's say that the energyBuffer is at the crit threshold, then it would be zero.
            //If the remaining energy is euqal to the energy buffer limit threshold, it is equal to 1.
            //So as we get closer to crit threshold, it will limit it closer to zero.

            //If the energy buffer is less then the crit threshold, it can be less than zero, leading to some odd results
            //If the reamining energy is greater than the limitThreshold, it is greater than 1, leading to a runaway situation
            const float remainingEnergyPercentage{remainingEnergy / m_energyBufferLimitThreshold};
            return tap::algorithms::limitVal(remainingEnergyPercentage, 0.0f, 1.0f);
        }
        else
        {
            return 1.0f;
        }
    }

    Joules PowerLimiter::getEnergyBuffer() const
    {
        const RefSerial::RefSerialData::Rx::RobotData& robotData{m_refereeSystem.getRobotData()};
        return Joules{robotData.chassis.powerBuffer};
    }
}