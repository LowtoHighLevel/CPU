#ifndef __DEV_H
#define __DEV_H

#define DEV_ROM
#define DEV_RAM
#define DEV_CHAR

#ifdef DEV_ROM
#include <dev/rom.h>
#endif

#ifdef DEV_RAM
#include <dev/ram.h>
#endif

#ifdef DEV_CHAR
#include <dev/char.h>
#endif

void init_devices();

#endif
