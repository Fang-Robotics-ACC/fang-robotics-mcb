#pragma once

#include "modded_cascade_position.hpp"

#include "telemetry/adapter/iangular_velocity_adapter.hpp"
#include "telemetry/adapter/iangular_position_adapter.hpp"

#include "wrap/trap/motor/dji_gm6020.hpp"
#include "wrap/trap/motor/dji_motor_aliases.hpp"
#include "wrap/trap/algorithms/ring_radians.hpp"

#include "wrap/units/units_alias.hpp"

#include <memory>

namespace fang::motor
{
    class ModdedCascadeGm6020
        :
        public ModdedCascadePosition<trap::motor::DjiMotorOutput, RPM>
    {
    public:
        using Motor = trap::motor::DjiGM6020;
        using PidMotor = ModdedCascadePosition<trap::motor::DjiMotorOutput, RPM>;

        struct Config{
            Motor::Config motorConfig;
            PidMotor::Config pidMotorConfig;
        };

        ModdedCascadeGm6020(
            Drivers& drivers,
            const Config& config,
            std::unique_ptr<MainModder> mainModder = std::make_unique<trap::algorithms::NullPidModder<RPM>>(),
            std::unique_ptr<IntermediateModder> intermediateModder  = std::make_unique<trap::algorithms::NullPidModder<trap::motor::DjiMotorOutput>>()
        ):
            PidMotor
            {make(drivers, config)}
        {
        }

    private:
        PidMotor make(Drivers& drivers, const Config& config)
        {
            auto motor{
                std::make_unique<Motor>(
                    drivers,
                    config.motorConfig
                )
            };

            auto positionTelemetry{
                std::make_unique<telemetry::IAngularPositionAdapter>(
                    *motor
                )
            };

            auto velocityTelemetry{
                std::make_unique<telemetry::IAngularVelocityAdapter>(
                    *motor
                )
            };

            return PidMotor{
                config.pidMotorConfig,
                std::move(motor),
                std::move(positionTelemetry),
                std::move(velocityTelemetry)
            };
        }
    };
}