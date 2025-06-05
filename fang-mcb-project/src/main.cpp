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
#include "control/chassis/chassis_subsystem.hpp"
#include "data/directionality.hpp"

#include <iostream>

/* define timers here -------------------------------------------------------*/
static constexpr float MAIN_LOOP_FREQUENCY = 500.0f;
tap::arch::PeriodicMilliTimer sendMotorTimeout(1000.0f / MAIN_LOOP_FREQUENCY);

// Place any sort of input/output initialization here. For example, place
// serial init stuff here.
static void initializeIo(Drivers *drivers_ptr);

// Anything that you would like to be called place here. It will be called
// very frequently. Use PeriodicMilliTimers if you don't want something to be
// called as frequently.
static void updateIo(Drivers *drivers_ptr);

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

    //Drivers& drivers_ptr{DoNotUse_getDriversReference()};
    Drivers *drivers_ptr = DoNotUse_getDrivers();

    Board::initialize();
    initializeIo(drivers_ptr);
    Robot robot{drivers_ptr};
    drivers_ptr->pwm.setTimerFrequency(tap::gpio::Pwm::TIMER1, Hertz{config::chassis::k_chassisPwmFreq}.to<double>());
    //control::chassis::ChassisSubsystem subsystem{*drivers_ptr, config::chassis::k_defaultConfig};

    robot.initializeSubsystemCommands();
    //subsystem.initialize();
    //Crash detection hack of hacks
    //If the code crashes, the blue light will stay on for 2 seconds
    //Crashes tend to result in the code rebooting
    drivers_ptr->leds.set(tap::gpio::Leds::Blue, true);
    modm::delay_ms(2000);
    //robot.initializeSubsystemCommands();

#ifdef PLATFORM_HOSTED
    tap::motor::motorsim::DjiMotorSimHandler::getInstance()->resetMotorSims();
    // Blocking call, waits until Windows Simulator connects.
    tap::communication::TCPServer::MainServer()->getConnection();
#endif
    while (1)
    {
        // do this as fast as you can
        PROFILE(drivers_ptr->profiler, updateIo, (drivers_ptr));

        if (sendMotorTimeout.execute())
        {
            PROFILE(drivers_ptr->profiler, drivers_ptr->bmi088.periodicIMUUpdate, ());
            PROFILE(drivers_ptr->profiler, drivers_ptr->commandScheduler.run, ());
            PROFILE(drivers_ptr->profiler, drivers_ptr->djiMotorTxHandler.encodeAndSendCanData, ());
            PROFILE(drivers_ptr->profiler, drivers_ptr->terminalSerial.update, ());
        }
        modm::delay_us(10);
    }
    return 0;
}

static void initializeIo(Drivers *drivers_ptr)
{
    drivers_ptr->analog.init();
    drivers_ptr->pwm.init();
    drivers_ptr->digital.init();
    drivers_ptr->leds.init();
    drivers_ptr->can.initialize();
    drivers_ptr->errorController.init();
    drivers_ptr->remote.initialize();
    drivers_ptr->bmi088.initialize(MAIN_LOOP_FREQUENCY, 0.1, 0);
    drivers_ptr->refSerial.initialize();
    drivers_ptr->terminalSerial.initialize();
    drivers_ptr->schedulerTerminalHandler.init();
    drivers_ptr->djiMotorTerminalSerialHandler.init();
}

static void updateIo(Drivers *drivers_ptr)
{
#ifdef PLATFORM_HOSTED
    tap::motor::motorsim::DjiMotorSimHandler::getInstance()->updateSims();
#endif

    drivers_ptr->canRxHandler.pollCanData();
    drivers_ptr->refSerial.updateSerial();
    drivers_ptr->remote.read();
    drivers_ptr->bmi088.read();
}
