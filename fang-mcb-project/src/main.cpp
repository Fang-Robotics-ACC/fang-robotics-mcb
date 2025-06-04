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
static void initializeIo(Drivers *drivers);

// Anything that you would like to be called place here. It will be called
// very frequently. Use PeriodicMilliTimers if you don't want something to be
// called as frequently.
static void updateIo(Drivers *drivers);

int main()
{
#ifdef PLATFORM_HOSTED
    std::cout << "Simulation starting..." << std::endl;
#endif
    std::cerr<< "fuck";

    /*
     * NOTE: We are using DoNotUse_getDrivers here because in the main
     *      robot loop we must access the singleton drivers to update
     *      IO states and run the scheduler.
     */
    Drivers *drivers = DoNotUse_getDrivers();
    //Robot robot{*drivers};
    //robot.initializeSubsystemCommands();

    Board::initialize();
    initializeIo(drivers);
    using namespace units::literals;

    constexpr Hertz k_pwmFrequency{400};
    drivers->pwm.setTimerFrequency(tap::gpio::Pwm::TIMER1, k_pwmFrequency.to<float>());
    using ChassisSubsystem = control::chassis::ChassisSubsystem;
    using ChassisDriveMotor = ChassisSubsystem::DriveMotor;
    constexpr ChassisDriveMotor::UnifiedProperties k_chassisUnifiedMotorProperties{24_V, data::motors::Directionality::BIDIRECTIONAL, 14};
    constexpr ChassisSubsystem::ChassisDimensionConfig k_chassisDimensionConfig{150_mm, 15_in, 13.5_in};
    constexpr ChassisSubsystem::ChassisMotorConfig k_chassisMotorConfig{
                                                                        k_chassisUnifiedMotorProperties,
                                                                        trap::gpio::PwmData{tap::gpio::Pwm::C1, k_pwmFrequency},
                                                                        trap::gpio::PwmData{tap::gpio::Pwm::C2, k_pwmFrequency},
                                                                        trap::gpio::PwmData{tap::gpio::Pwm::C3, k_pwmFrequency},
                                                                        trap::gpio::PwmData{tap::gpio::Pwm::C4, k_pwmFrequency}};
    constexpr ChassisSubsystem::ChassisConfig k_chassisConfig{k_chassisDimensionConfig, k_chassisMotorConfig};
    control::chassis::ChassisSubsystem chassisSubsystem{*drivers, k_chassisConfig};

    //Test forward movement
    chassisSubsystem.initialize();
    modm::delay_ms(5000);
    chassisSubsystem.setTranslation(physics::Velocity2D{0_mph, 100_mph});

    ///Test strafe movement
    //chassisSubsystem.setTranslation(physics::Velocity2D{1_mph, 0_mph});

    ////Test rotational movement
    //chassisSubsystem.setRotation(10_rpm);





#ifdef PLATFORM_HOSTED
    tap::motor::motorsim::DjiMotorSimHandler::getInstance()->resetMotorSims();
    // Blocking call, waits until Windows Simulator connects.
    tap::communication::TCPServer::MainServer()->getConnection();
#endif

    while (1)
    {
        // do this as fast as you can
        PROFILE(drivers->profiler, updateIo, (drivers));

        if (sendMotorTimeout.execute())
        {
            PROFILE(drivers->profiler, drivers->bmi088.periodicIMUUpdate, ());
            PROFILE(drivers->profiler, drivers->commandScheduler.run, ());
            PROFILE(drivers->profiler, drivers->djiMotorTxHandler.encodeAndSendCanData, ());
            PROFILE(drivers->profiler, drivers->terminalSerial.update, ());
        }
        modm::delay_us(10);
    }
    return 0;
}

static void initializeIo(Drivers *drivers)
{
    drivers->analog.init();
    drivers->pwm.init();
    drivers->digital.init();
    drivers->leds.init();
    drivers->can.initialize();
    drivers->errorController.init();
    drivers->remote.initialize();
    drivers->bmi088.initialize(MAIN_LOOP_FREQUENCY, 0.1, 0);
    drivers->refSerial.initialize();
    drivers->terminalSerial.initialize();
    drivers->schedulerTerminalHandler.init();
    drivers->djiMotorTerminalSerialHandler.init();
}

static void updateIo(Drivers *drivers)
{
#ifdef PLATFORM_HOSTED
    tap::motor::motorsim::DjiMotorSimHandler::getInstance()->updateSims();
#endif

    drivers->canRxHandler.pollCanData();
    drivers->refSerial.updateSerial();
    drivers->remote.read();
    drivers->bmi088.read();
}
