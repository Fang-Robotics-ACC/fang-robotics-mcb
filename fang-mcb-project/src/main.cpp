/*
 * Copyright (c) 2020-2021 Fang-Robotics
 *
 * This file is part of fang-mcb.
 *
 * fang-mcb is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * fang-mcb is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with fang-mcb.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifdef PLATFORM_HOSTED
/* hosted environment (simulator) includes --------------------------------- */
#include <iostream>

#include "tap/communication/tcp-server/tcp_server.hpp"
#include "tap/motor/motorsim/dji_motor_sim_handler.hpp"
#endif

#include "tap/board/board.hpp"

#include "modm/architecture/interface/delay.hpp"

/* arch includes ------------------------------------------------------------*/
#include "tap/architecture/periodic_timer.hpp"
#include "tap/architecture/profiler.hpp"
#include "tap/motor/dji_motor.hpp"

/* communication includes ---------------------------------------------------*/
#include "drivers.hpp"
#include "drivers_singleton.hpp"

/* error handling includes --------------------------------------------------*/
#include "tap/errors/create_errors.hpp"

/* control includes ---------------------------------------------------------*/
#include "tap/architecture/clock.hpp"
#include "units.h"
#include "control/robot.hpp"
#include "configuration/chassis_config.hpp"
#include "motors/gearboxrepeatultramk2.hpp"
#include "trap/motor/dji_m2006.hpp"
#include "trap/motor/dji_gm6020.hpp"
#include "control/chassis/chassis_subsystem.hpp"
#include "data/directionality.hpp"
#include "control/turret/gimbal_system.hpp"
#include "control/turret/feeder_system.hpp"
#include "control/turret/ammo_booster_system.hpp"

#include <iostream>

/* define timers here -------------------------------------------------------*/
static constexpr float MAIN_LOOP_FREQUENCY = 500.0f;
tap::arch::PeriodicMilliTimer sendMotorTimeout(1000.0f / MAIN_LOOP_FREQUENCY);

// Place any sort of input/output initialization here. For example, place
// serial init stuff here.
static void initializeIo(Drivers& drivers);

// Anything that you would like to be called place here. It will be called
// very frequently. Use PeriodicMilliTimers if you don't want something to be
// called as frequently.
static void updateIo(Drivers& drivers);

int main()
{
#ifdef PLATFORM_HOSTED
    std::cout << "Simulation starting..." << std::endl;
#endif

    /*
     * NOTE: We are using DoNotUse_getDrivers here because in the main
     *      robot loop we must access the singleton drivers_ptr to update
     *      IO states and run the scheduler.
     */

    Drivers& drivers{DoNotUse_getDriversReference()};


    Board::initialize();
    initializeIo(drivers);

    Robot robot{drivers};
    robot.initialize();

    //robot.initializeSubsystemCommands();
    const trap::motor::DjiSpeedPid::Config pitchPidConfig{50000, 1000, 20 ,100, trap::motor::DjiGM6020::k_maxOutput};
    const trap::motor::DjiGM6020::Config pitchConfig{static_cast<tap::motor::MotorId>(tap::motor::MOTOR2), tap::can::CanBus::CAN_BUS1, "epic", true,  1.0, pitchPidConfig, false};
    //trap::motor::DjiGM6020 motor{drivers, config};


    const trap::motor::DjiSpeedPid::Config yawPidConfig{50000, 1000, 0 ,100, trap::motor::DjiGM6020::k_maxOutput};
    const trap::motor::DjiGM6020::Config yawConfig{static_cast<tap::motor::MotorId>(tap::motor::MOTOR1), tap::can::CanBus::CAN_BUS1, "epi", true,  1.0, yawPidConfig, false};
    //trap::motor::DjiGM6020 motor2{drivers, config2};


    //using GimbalSystem = control::turret::GimbalSystem;
    //const GimbalSystem::Config gimbalConfig
    //{
    //    -10_deg,
    //    10_deg,
    //    pitchConfig,
    //    yawConfig
    //};
    //GimbalSystem gimbal{drivers, gimbalConfig};
    //gimbal.initialize();
    //gimbal.setPitch(0_deg);

    using FeederSystem = control::turret::FeederSystem;

    static const trap::motor::DjiSpeedPid::Config feederMotorPidConfig 
    {
        5,
        100,
        0,
        100,
        trap::motor::DjiM2006::k_maxOutput
    };

    static const trap::motor::DjiM2006::Config feederMotorConfig
    { 
        tap::motor::MOTOR3,
        tap::can::CanBus::CAN_BUS1,
        "epic",
        false,
        1.0,
        feederMotorPidConfig
    };



    static const FeederSystem::Config feederConfig
    {
        7,
        25_Hz,
        feederMotorConfig
    };


    using AmmoBooster = control::turret::AmmoBoosterSystem;
    using Flywheel = control::turret::FlywheelSystem;

    static const trap::motor::DjiSpeedPid::Config flywheelMotorPidConfig 
    {
        10,
        10,
        0,
        100,
        trap::motor::DjiM3508::k_maxOutput
    };

    static const trap::motor::DjiSpeedPid::Config flywheelMotorPidConfigRight
    {
        10,
        10,
        0,
        100,
        trap::motor::DjiM3508::k_maxOutput
    };

    static const Flywheel::DriveMotor::Config leftFlywheelMotorConfig
    { 
        static_cast<tap::motor::MotorId>(tap::motor::MOTOR8),
        tap::can::CanBus::CAN_BUS1,
        "leftFlywheel",
        false,
        1.0,
        flywheelMotorPidConfig 
    };
    static const Flywheel::Config leftFlywheelConfig 
    {
        150_mm,
        leftFlywheelMotorConfig
    };

    static const Flywheel::DriveMotor::Config rightFlywheeMotorConfig 
    { 
        static_cast<tap::motor::MotorId>(tap::motor::MOTOR7),
        tap::can::CanBus::CAN_BUS1,
        "rightFlywheel",
        true,
        1.0,
        flywheelMotorPidConfigRight
    };

    static const Flywheel::Config rightFlywheelConfig
    {
        150_mm,
        rightFlywheeMotorConfig
    };

    static const AmmoBooster::Config ammoBoosterConfig
    {
        50_fps,
        leftFlywheelConfig,
        rightFlywheelConfig
    };

    //Flywheel::DriveMotor testmotor{drivers, leftFlywheelMotorConfig};
    Drivers& drivers2{drivers};
    Drivers& drivers3{drivers2};
    //testmotor.initialize();
    //testmotor.setDesiredOutput(10000);
    //tap::motor::DjiMotor djiMotor{&drivers3, tap::motor::MOTOR3, tap::can::CanBus::CAN_BUS1, false, "test"};
    //djiMotor.initialize();
    //djiMotor.setDesiredOutput(50000);
    //testmotor.initialize();
    //testmotor.setTargetSpeed(1000_rpm);

    //Flywheel testFlywheel{drivers, leftFlywheelConfig};
    //testFlywheel.initialize();
    //testFlywheel.setTargetRimSpeed(10_mps);

    //Flywheel testFlywheelRight{drivers, rightFlywheelConfig};
    //testFlywheelRight.initialize();
    //testFlywheelRight.setTargetRimSpeed(10_mps);

    //AmmoBooster booster{drivers, ammoBoosterConfig};
    //booster.initialize();
    //booster.autoFireOn();

    FeederSystem feeder{drivers, feederConfig};
    feeder.initialize();
    feeder.feedOn();

    //trap::motor::DjiM2006 testFeeder{drivers, feederMotorConfig};
    //testFeeder.initialize();
    //testFeeder.setDesiredOutput(1000);



    //djiDriver.initialize();
    //djiDriver.setDesiredOutput(10000);


    //motor.setDesiredOutput(1000);


#ifdef PLATFORM_HOSTED
    tap::motor::motorsim::DjiMotorSimHandler::getInstance()->resetMotorSims();
    // Blocking call, waits until Windows Simulator connects.
    tap::communication::TCPServer::MainServer()->getConnection();
#endif
    while (1)
    {
        //testmotor.update();
        //testFlywheel.update();
        //testFlywheelRight.update();
        //booster.update();
        //feeder.update();
        //gimbal.update();
        //gimbal.setPitch(30_deg * drivers.remote.getChannel(tap::communication::serial::Remote::Channel::LEFT_VERTICAL));
        //gimbal.setYaw(300_deg * drivers.remote.getChannel(tap::communication::serial::Remote::Channel::LEFT_HORIZONTAL));
        // do this as fast as you can
        PROFILE(drivers.profiler, updateIo, (drivers));

        if (sendMotorTimeout.execute())
        {
            PROFILE(drivers.profiler, drivers.bmi088.periodicIMUUpdate, ());
            PROFILE(drivers.profiler, drivers.commandScheduler.run, ());
            PROFILE(drivers.profiler, drivers.djiMotorTxHandler.encodeAndSendCanData, ());
            PROFILE(drivers.profiler, drivers.terminalSerial.update, ());
        }
        modm::delay_us(10);
    }
    return 0;
}

static void initializeIo(Drivers& drivers)
{
    drivers.analog.init();
    drivers.pwm.init();
    drivers.digital.init();
    drivers.leds.init();
    drivers.can.initialize();
    drivers.errorController.init();
    drivers.remote.initialize();
    drivers.bmi088.initialize(MAIN_LOOP_FREQUENCY, 0.1, 0);
    drivers.refSerial.initialize();
    drivers.terminalSerial.initialize();
    drivers.schedulerTerminalHandler.init();
    drivers.djiMotorTerminalSerialHandler.init();
}

static void updateIo(Drivers& drivers)
{
#ifdef PLATFORM_HOSTED
    tap::motor::motorsim::DjiMotorSimHandler::getInstance()->updateSims();
#endif

    drivers.canRxHandler.pollCanData();
    drivers.refSerial.updateSerial();
    drivers.remote.read();
    drivers.bmi088.read();
}
