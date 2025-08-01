#include "robot/variant/pierce/custom_variant/subsystem/pierce_mecanum_drive.hpp"
#include "wrap/units/units_alias.hpp"

#include <gtest/gtest.h>

namespace fang::chassis
{
    //Check if there are no memory leaks
    TEST(PierceMecanumDrive, validity)
    {
        using namespace units::literals;

        Drivers drivers{};
        const PierceMecanumDrive::Motor::Config kMockMotorConfig
        {
            .controllerInputVoltage = 24_V,
            .pwmData = {tap::gpio::Pwm::C1, 500_Hz},
            .directionality = motor::Directionality::BIDIRECTIONAL,
            .inverted = false,
            .gearRatio = 14
        };

        const PierceMecanumDrive::MotorConfigs kMotorConfigs 
        {
            kMockMotorConfig,
            kMockMotorConfig,
            kMockMotorConfig,
            kMockMotorConfig
        };

        const PierceMecanumDrive::PowerLimiter::Config kPowerLimiterConfig
        {
            .startingEnergyBuffer = 80_J,
            .energyBufferLimitThreshold = 5_J,
            .energyBufferCritThreshold = 10_J,
        };

        const FieldMecanumLogic::Config kFieldMecanumConfig
        {
            .horizontalWheelDistance = 1_m,
            .verticalWheelDistance = 1_m,
            .wheelRadius = 0.25_m
        };

        const PierceMecanumDrive::Config kConfig
        {
            .motorConfigs = kMotorConfigs,
            .powerLimiterConfig = kPowerLimiterConfig,
            .fieldMecanumConfig = kFieldMecanumConfig,
            .chassisPwmFrequency = 250_Hz,
            .pwmTimer = tap::gpio::Pwm::TIMER1
        };
        PierceMecanumDrive mecanumDrive{drivers, kConfig};
        mecanumDrive.initialize();
        mecanumDrive.refresh();
        mecanumDrive.setTargetTranslation({1_mph, 12_mph});
    }

}