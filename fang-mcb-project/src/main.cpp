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
#include "trap/motor/dji_gm6020.hpp"
#include "control/chassis/chassis_subsystem.hpp"
#include "data/directionality.hpp"

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
    //Robot robot{drivers};


    Board::initialize();
    initializeIo(drivers);

    //robot.initializeSubsystemCommands();
    trap::motor::DjiSpeedPid::Config motorPidConfig{50000, 1000, 20 ,100, trap::motor::DjiGM6020::k_maxOutput};
    trap::motor::DjiGM6020::Config config{static_cast<tap::motor::MotorId>(tap::motor::MOTOR2), tap::can::CanBus::CAN_BUS1, "epic", true,  1.0, motorPidConfig, false};
    trap::motor::DjiGM6020 motor{drivers, config};


    trap::motor::DjiSpeedPid::Config motorPidConfig2{50000, 1000, 0 ,100, trap::motor::DjiGM6020::k_maxOutput};
    trap::motor::DjiGM6020::Config config2{static_cast<tap::motor::MotorId>(tap::motor::MOTOR1), tap::can::CanBus::CAN_BUS1, "epi", true,  1.0, motorPidConfig2, false};
    trap::motor::DjiGM6020 motor2{drivers, config2};


    //djiDriver.initialize();
    //djiDriver.setDesiredOutput(10000);

    motor.initialize();
    motor2.initialize();

    bool ledFlash{motor.isMotorOnline()};
    drivers.leds.set(tap::gpio::Leds::Blue, ledFlash);
    motor.setTargetPosition(0.0_rad);
    //motor.setDesiredOutput(1000);


#ifdef PLATFORM_HOSTED
    tap::motor::motorsim::DjiMotorSimHandler::getInstance()->resetMotorSims();
    // Blocking call, waits until Windows Simulator connects.
    tap::communication::TCPServer::MainServer()->getConnection();
#endif
    while (1)
    {
        motor.update();
        motor2.update();
        motor.setTargetPosition(30_deg * drivers.remote.getChannel(tap::communication::serial::Remote::Channel::LEFT_VERTICAL));
        motor2.setTargetPosition(300_deg * drivers.remote.getChannel(tap::communication::serial::Remote::Channel::LEFT_HORIZONTAL));
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
