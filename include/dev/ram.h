#ifndef __DEV_RAM_H
#define __DEV_RAM_H

#include <stdint.h>
#include <defs.h>
#include <dev/dev.h>
#include <dev/rom.h>

#ifndef RAM_SIZE
    #define RAM_SIZE (1024 * 8)
#endif
#ifndef RAM_ADDR
    #ifdef DEV_ROM
        #define RAM_ADDR (ROM_ADDR + ROM_SIZE)
    #else
        #define RAM_ADDR (0)
    #endif
#endif
void ram_init();

#endif