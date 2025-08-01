#include "control/chassis/drive/quad_drive/power_quad_drive/ultra_mk2_power_quad_drive.hpp"
#include "wrap/units/units_alias.hpp"

#include "driver/drivers.hpp"
#include "rail/mock/chassis/ipower_limiter_system_mock.hpp"

#include <gtest/gtest.h>
namespace fang::chassis
{
    TEST(RepeatUltraMk2PowerDrive, validity)
    {
        /**
        * Check if there are no crashes with the basic functions
        */
        using namespace units::literals;
        UltraMk2PowerQuadDrive::Motor::Config mockMotorConfig
        {
            .controllerInputVoltage = 24_V,
            .pwmData = {tap::gpio::Pwm::C1, 500_Hz},
            .directionality = motor::Directionality::BIDIRECTIONAL,
            .inverted = false,
            .gearRatio = 14
        };
        UltraMk2PowerQuadDrive::Config config
        {
            mockMotorConfig,
            mockMotorConfig,
            mockMotorConfig,
            mockMotorConfig
        };
        Drivers drivers{};

        UltraMk2PowerQuadDrive quadDrive_
        {
            drivers,
            std::move(std::make_unique<rail::chassis::IPowerLimiterSystemMock>()),
            config
        };

        quadDrive_.initialize();
        quadDrive_.update();
        quadDrive_.refresh();
    }
    
}