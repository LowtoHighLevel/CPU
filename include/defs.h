#ifndef DEFS_H
#define DEFS_H

#include <stdint.h>

#ifndef LTHLV2_TYPE
#define LTHLV2_TYPE 32
#endif

typedef uint32_t instr_t;

#if LTHLV2_TYPE == 32
#define DATA_WIDTH 32
typedef uint32_t data_t;
#define STARTVEC 0xFFFFFFFC
#elif LTHLV2_TYPE == 64
#define DATA_WIDTH 64
typedef uint64_t data_t;
#define STARTVEC 0xFFFFFFFFFFFFFFFC
#endif

#endif