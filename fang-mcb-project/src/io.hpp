#ifndef FANG_ROBOTICS_MCB_IO_HPP
#define FANG_ROBOTICS_MCB_IO_HPP
/**
 * How often the main loop should loop
 */
static constexpr float kMainLoopFrequency{500.0f}; //Hertz

/**
 * Place any sort of input/output initialization here. For example, place
 * serial init stuff here.
 */
void initializeIo();

/**
 * Anything that you would like to be called place here. It will be called
 * very frequently. Use PeriodicMilliTimers if you don't want something to be
 * called as frequently.
 */
void updateIo();
#endif