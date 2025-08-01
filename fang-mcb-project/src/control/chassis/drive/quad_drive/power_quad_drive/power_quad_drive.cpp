#include "power_quad_drive.hpp"
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
            const QuadRPM scaledWheelSpeeds{wheelSpeeds * powerLimiter_->getPowerLimitRatio()};
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