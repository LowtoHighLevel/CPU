#ifndef __DEV_H
#define __DEV_H

#include <defs.h>

#ifdef DEV_ROM
#include <dev/rom.h>
#endif

#ifdef DEV_RAM
#include <dev/ram.h>
#endif

#ifdef DEV_CHAR
#include <dev/char.h>
#endif

/**
 * Initializes Devices
 */
void init_devices();

#endif
