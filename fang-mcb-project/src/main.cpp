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
#include "driver/drivers.hpp"
#include "driver/drivers_singleton.hpp"

/* error handling includes --------------------------------------------------*/
#include "tap/errors/create_errors.hpp"

/* control includes ---------------------------------------------------------*/
#include "tap/architecture/clock.hpp"

#include "io.hpp"
#include "units.h"
#include "robot/robot.hpp"

#include <cassert>
#include <iostream>

/* define timers here -------------------------------------------------------*/
tap::arch::PeriodicMilliTimer sendMotorTimeout(1000.0f / kMainLoopFrequency);

int main()
{
    assert(false && "This assertion failed");
    #ifdef PLATFORM_HOSTED
    std::cout << "Simulation starting..." << std::endl;
    #endif

    Drivers& drivers{DriversSingleton::getDrivers()};

    Board::initialize();
    drivers.initializeIo();

    //This prevents the large size of the robot class from hoarding the stack
    //which causes annoying stack overflow issues
    //static classes are in static memory instead of stack memory
    static Robot robot{drivers, k_robotConfig};

    robot.initialize();

    #ifdef PLATFORM_HOSTED
        tap::motor::motorsim::DjiMotorSimHandler::getInstance()->resetMotorSims();
        // Blocking call, waits until Windows Simulator connects.
        tap::communication::TCPServer::MainServer()->getConnection();
    #endif

    while (1)
    {
        drivers.update();

        //Prevent motor signals from being spammed
        if (sendMotorTimeout.execute())
        {
            drivers.motorTimeoutUpdate();
        }

        modm::delay_us(10); //Any longer and refSerial will not work
    }
    return 0;
}