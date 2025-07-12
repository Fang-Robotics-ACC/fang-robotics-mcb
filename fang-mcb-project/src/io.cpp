#include "io.hpp"

#ifdef PLATFORM_HOSTED
/* hosted environment (simulator) includes --------------------------------- */
#include <iostream>

#include "tap/communication/tcp-server/tcp_server.hpp"
#include "tap/motor/motorsim/dji_motor_sim_handler.hpp"
#endif

void initializeIo(Drivers& drivers)
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

void updateIo(Drivers& drivers)
{
    #ifdef PLATFORM_HOSTED
    tap::motor::motorsim::DjiMotorSimHandler::getInstance()->updateSims();
    #endif

    drivers.canRxHandler.pollCanData();
    drivers.refSerial.updateSerial();
    drivers.remote.read();
    drivers.bmi088.read();
}
