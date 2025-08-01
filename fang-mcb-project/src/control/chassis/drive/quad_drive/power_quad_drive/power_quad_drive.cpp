#include "power_quad_drive.hpp"

#include "system/assert/fang_assert.hpp"
namespace fang::chassis
{
        PowerQuadDrive::PowerQuadDrive 
        (
            Drivers& drivers,
            Motors&& motors,
            std::unique_ptr<IPowerLimiterSystem> powerLimiter
        ):
            BaseQuadDrive{drivers, std::move(motors)},
            powerLimiter_{std::move(powerLimiter)}
        {
        }

        void PowerQuadDrive::setTargetWheelSpeeds(const QuadRPM& wheelSpeeds)
        {
            const double powerLimitRatio(powerLimiter_->getPowerLimitRatio());
            FANG_ASSERT(0 <= powerLimitRatio, "The limit ratio should not reverse direction!!!");
            const QuadRPM scaledWheelSpeeds{wheelSpeeds * powerLimitRatio};
            BaseQuadDrive::setTargetWheelSpeeds(scaledWheelSpeeds);
        }

        void PowerQuadDrive::initialize()
        {
            powerLimiter_->initialize();
            BaseQuadDrive::initialize();
        }

        void PowerQuadDrive::update()
        {
            powerLimiter_->update();
            BaseQuadDrive::update();
        }

        void PowerQuadDrive::refresh()
        {
            //Taproot compatibility
            update();
        }
}