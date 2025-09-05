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
#include "modm/architecture/interface/assert.hpp"
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

#include "tap/communication/serial/uart_terminal_device.hpp"

#include "io.hpp"
#include "units.h"
#include "robot/robot.hpp"

#include <cassert>
#include <iostream>

int main()
{

    #ifdef PLATFORM_HOSTED
    std::cout << "Simulation starting..." << std::endl;
    #endif

    fang::Drivers& drivers{fang::DriversSingleton::getDrivers()};

    tap::communication::serial::UartTerminalDevice testUart{&drivers};
    Board::initialize();
    drivers.initializeIo();

    testUart.initialize();

    /*
     * 
     * This prevents the large size of the robot class from hoarding the stack
     * which causes annoying stack overflow issues
     * static classes are in static memory instead of stack memory
     */
    static Robot robot{drivers, k_robotConfig};

    robot.initialize();

    #ifdef PLATFORM_HOSTED
        tap::motor::motorsim::DjiMotorSimHandler::getInstance()->resetMotorSims();
        // Blocking call, waits until Windows Simulator connects.
        tap::communication::TCPServer::MainServer()->getConnection();
    #endif

    /*
     * From ARUW's Eli:
     * "id say you want your main loop speed to be at minimum 8khz for how the dji
     * motors work, as for the main loop, you dont need faster control than 1khz,
     * and 500 works just as well, at 1khz you could overrun with more control so
     * 500 gives you more time "
     */
    static tap::arch::PeriodicMilliTimer mainLoopTimer(1000.0f / kMainLoopFrequency);

    // Prevents the faster loop from going too fast (it handles io)
    static constexpr Microseconds kFastloopDelay{10};
    while (1)
    {
        drivers.update();

        if (mainLoopTimer.execute())
        {
            testUart.write('z');
            drivers.motorTimeoutUpdate();
        }

        // Any longer and refSerial will not work
        modm::delay_us(static_cast<uint32_t>(kFastloopDelay));
    }
    return 0;
}