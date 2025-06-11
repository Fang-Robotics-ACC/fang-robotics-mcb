#ifndef FANG_ROBOTICS_MCB_PIERCE_TURRET_CONFIG_HPP
#define FANG_ROBOTICS_MCB_PIERCE_TURRET_CONFIG_HPP
#include "control/turret/turret_subsystem.hpp"
#include "configuration/motion/turret_motion_config.hpp"
#include "unitaliases.hpp"

namespace control 
{
    namespace pierceConfig
    {
        using namespace units::literals;
        static const MetersPerSecond k_ammoBoosterVelocity{20_fps};
        static const Degrees k_gimbalYawHomeOffset{0};
        static const Degrees k_minPitch{-30};
        static const Degrees k_maxPitch{30};
        static const int k_roundsPerRevolution{7};
        static const Hertz k_fireRate{10};
        static const double k_feederMotorGearRatio{trap::motor::DjiM2006::k_factoryGearboxRatio};
        static const config::motion::TurretConfig k_pierceTurretMotionConfig
        {
            10_rpm,
            10_rpm    
        };

        static const Meters k_flywheelRadius{30_mm};
        static const tap::can::CanBus k_turretCanBus{tap::can::CanBus::CAN_BUS1};
        static const double k_flywheelGearRatio{1.0};

        using FlywheelMotor = turret::FlywheelSystem::DriveMotor;

        static const FlywheelMotor::DjiSpeedPid::Config k_flywheelPidConfig
        {
            1000,
            1,
            20,
            100,
            FlywheelMotor::k_maxOutput
        };

        static const turret::FlywheelSystem::DriveMotor::Config k_leftFlywheelMotorConfig
        {
            tap::motor::MOTOR4,
            k_turretCanBus,
            "leftFlywheelMotor",
            false,
            k_flywheelGearRatio,
            k_flywheelPidConfig
        };

        static const turret::FlywheelSystem::DriveMotor::Config k_rightFlywheelMotorConfig
        {
            tap::motor::MOTOR5,
            k_turretCanBus,
            "rightFlywheelMotor",
            true,
            k_flywheelGearRatio,
            k_flywheelPidConfig
        };

        static const turret::FlywheelSystem::Config k_leftFlywheelConfig
        {
            k_flywheelRadius,
            k_leftFlywheelMotorConfig
        };

        static const turret::FlywheelSystem::Config k_rightFlywheelConfig
        {
            k_flywheelRadius,
            k_rightFlywheelMotorConfig 
        };

        static const turret::AmmoBoosterSystem::Config k_ammoBoosterConfig
        {
            k_ammoBoosterVelocity,
            k_leftFlywheelConfig,
            k_rightFlywheelConfig
        };

        using FeederMotor = turret::FeederSystem::DriveMotor;

        static const FeederMotor::DjiSpeedPid::Config k_feederMotorPidConfig
        {
            1000,
            1,
            20,
            100,
            2000
        };

        static const FeederMotor::Config k_feederMotorConfig
        {
            tap::motor::MOTOR3,
            k_turretCanBus,
            "feederMotor",
            false,
            k_feederMotorGearRatio,
            k_feederMotorPidConfig 
        };

        static const turret::FeederSystem::Config k_feederConfig
        {
            k_roundsPerRevolution,
            k_fireRate,
            k_feederMotorConfig
        };

        using GimbalMotor = turret::GimbalSystem::PositionMotor;

        static const GimbalMotor::DjiPositionPid::Config k_pitchMotorPidConfig
        {
            100,
            1,
            10,
            20,
            GimbalMotor::k_maxOutput
        };

        static const GimbalMotor::Config k_pitchMotorConfig 
        {
            tap::motor::MOTOR2,
            k_turretCanBus,
            "pitchMotor",
            false,
            1.0,
            k_pitchMotorPidConfig
        };

        static const GimbalMotor::DjiPositionPid::Config k_yawMotorPidConfig
        {
            100,
            1,
            10,
            20,
            GimbalMotor::k_maxOutput
        };

        static const GimbalMotor::Config k_yawMotorConfig 
        {
            tap::motor::MOTOR1,
            k_turretCanBus,
            "pitchMotor",
            false,
            1.0,
            k_yawMotorPidConfig 
        };

        static const turret::GimbalSystem::Config k_gimbalConfig
        {
            k_minPitch,
            k_maxPitch,
            k_pitchMotorConfig,
            k_yawMotorConfig
        };


        static const turret::TurretSubsystem::Config k_turretConfig
        {
            k_gimbalYawHomeOffset,
            k_ammoBoosterConfig,
            k_feederConfig,
            k_gimbalConfig
        };
    }
}
#endif