#pragma once

/**
 * This prevents the call stack from being yeeted
 * This will freeze the system until a power reset
 * or an eprom flash occurs.
 */
#define FREEZE_SYSTEM() \
    {                   \
        while(true)     \
        {}              \
    }                   \

