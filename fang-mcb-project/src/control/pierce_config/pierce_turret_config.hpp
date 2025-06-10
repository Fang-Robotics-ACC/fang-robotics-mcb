#ifndef FANG_ROBOTICS_MCB_PIERCE_TURRET_CONFIG_HPP
#define FANG_ROBOTICS_MCB_PIERCE_TURRET_CONFIG_HPP
#include "control/turret/turret_subsystem.hpp"
#include "configuration/motion/turret_motion_config.hpp"
#include "unitaliases.hpp"

namespace control 
{
    namespace pierce
    {
        using namespace units::literals;
        const MetersPerSecond k_ammoBoosterVelocity{20_fps};
        const Degrees k_gimbalYawHomeOffset{0};
        const Degrees k_minPitch{-30};
        const Degrees k_maxPitch{30};
        const int k_roundsPerRevolution{7};
        const Hertz k_fireRate{10};
        const double k_feederMotorGearRatio{trap::motor::DjiM2006::k_factoryGearboxRatio};
        const config::motion::TurretConfig k_pierceTurretMotionConfig
        {
            10_rpm,
            10_rpm    
        };

        const Meters k_flywheelRadius{30_mm};
        const tap::can::CanBus k_turretCanBus{tap::can::CanBus::CAN_BUS1};
        const double k_flywheelGearRatio{1.0};

        using FlywheelMotor = turret::FlywheelSystem::DriveMotor;

        const FlywheelMotor::DjiSpeedPid::Config k_flywheelPidConfig
        {
            1000,
            1,
            20,
            100,
            FlywheelMotor::k_maxOutput
        };

        const turret::FlywheelSystem::DriveMotor::Config k_leftFlywheelMotorConfig
        {
            tap::motor::MOTOR4,
            k_turretCanBus,
            "leftFlywheelMotor",
            false,
            k_flywheelGearRatio,
            k_flywheelPidConfig
        };

        const turret::FlywheelSystem::DriveMotor::Config k_rightFlywheelMotorConfig 
        {
            tap::motor::MOTOR5,
            k_turretCanBus,
            "rightFlywheelMotor",
            true,
            k_flywheelGearRatio,
            k_flywheelPidConfig
        };

        const turret::FlywheelSystem::Config k_leftFlywheelConfig
        {
            k_flywheelRadius,
            k_leftFlywheelMotorConfig
        };

        const turret::FlywheelSystem::Config k_rightFlywheelConfig 
        {
            k_flywheelRadius,
            k_rightFlywheelMotorConfig 
        };

        const turret::AmmoBoosterSystem::Config k_ammoBoosterConfig
        {
            k_ammoBoosterVelocity,
            k_leftFlywheelConfig,
            k_rightFlywheelConfig
        };

        using FeederMotor = turret::FeederSystem::DriveMotor;

        const FeederMotor::DjiSpeedPid::Config k_feederMotorPidConfig
        {
            1000,
            1,
            20,
            100,
            FeederMotor::k_maxOutput
        };

        const FeederMotor::Config k_feederMotorConfig
        {
            tap::motor::MOTOR3,
            k_turretCanBus,
            "feederMotor",
            false,
            k_feederMotorGearRatio,
            k_feederMotorPidConfig 
        };

        const turret::FeederSystem::Config k_feederConfig
        {
            k_roundsPerRevolution,
            k_fireRate,
            k_feederMotorConfig
        };

        using GimbalMotor = turret::GimbalSystem::PositionMotor;

        const GimbalMotor::DjiPositionPid::Config k_pitchMotorPidConfig
        {
            100,
            1,
            10,
            20,
            GimbalMotor::k_maxOutput
        };

        const GimbalMotor::Config k_pitchMotorConfig 
        {
            tap::motor::MOTOR2,
            k_turretCanBus,
            "pitchMotor",
            false,
            1.0,
            k_pitchMotorPidConfig
        };

        const GimbalMotor::DjiPositionPid::Config k_yawMotorPidConfig
        {
            100,
            1,
            10,
            20,
            GimbalMotor::k_maxOutput
        };

        const GimbalMotor::Config k_yawMotorConfig 
        {
            tap::motor::MOTOR2,
            k_turretCanBus,
            "pitchMotor",
            false,
            1.0,
            k_yawMotorPidConfig 
        };

        const turret::GimbalSystem::Config k_gimbalConfig
        {
            k_minPitch,
            k_maxPitch,
            k_pitchMotorConfig,
            k_yawMotorConfig
        };


        const turret::TurretSubsystem::Config k_turretConfig
        {
            k_gimbalYawHomeOffset,
            k_ammoBoosterConfig,
            k_feederConfig,
            k_gimbalConfig
        };
    }
}
#endif