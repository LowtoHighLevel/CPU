#ifndef DEFS_H
#define DEFS_H

#include <stdint.h>

#ifndef DEV
#define DEV_LEGACY
#endif

#ifdef DEV_LEGACY
#define DEV_ROM
#define DEV_RAM
#define DEV_CHAR
#endif

#ifndef CPUTYP
#define CPUTYP 32
#endif

typedef uint32_t instr_t;

#if CPUTYP == 32
#define DATA_WIDTH 32
typedef uint32_t data_t;
#define STARTVEC (uint32_t)(0 - sizeof(uint32_t))
#endif

#endif
