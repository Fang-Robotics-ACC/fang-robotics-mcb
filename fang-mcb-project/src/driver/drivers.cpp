#include "driver/drivers.hpp"
#include "io.hpp"

#include "tap/architecture/profiler.hpp"

namespace fang
{
    void Drivers::initializeIo()
    {   
        analog.init();
        pwm.init();
        digital.init();
        leds.init();
        can.initialize();
        errorController.init();
        remote.initialize();
        bmi088.initialize(kMainLoopFrequency, 0.1, 0);
        refSerial.initialize();
        coolSerialUart.initialize();
        //terminalSerial.initialize();
        schedulerTerminalHandler.init();
        djiMotorTerminalSerialHandler.init();
    }

    void Drivers::update()
    {
        coolSerialUart.update();
        PROFILE(profiler, updateIo, ());
    }

    void Drivers::updateIo()
    {
        canRxHandler.pollCanData();
        refSerial.updateSerial();
        remote.read();
        bmi088.read();
    }

    void Drivers::motorTimeoutUpdate()
    {
        PROFILE(profiler, bmi088.periodicIMUUpdate, ());
        PROFILE(profiler, commandScheduler.run, ());
        PROFILE(profiler, djiMotorTxHandler.encodeAndSendCanData, ());
        //PROFILE(profiler, terminalSerial.update, ());
    }

    void Drivers::kill()
    {
        //Pwm controllers will stick to the last state
        //It is uesful to set them all to zero to prevent
        //The robot from flailing if emergency shutdown is initiated
        pwm.writeAllZeros();
    }
}