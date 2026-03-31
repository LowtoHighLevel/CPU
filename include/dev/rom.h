#ifndef __DEV_ROM_H
#define __DEV_ROM_H

#include <dev/dev.h>

#ifdef DEV_ROM

#include <stdint.h>
#include <defs.h>

#ifndef ROM_SIZE
    #define ROM_SIZE (1024 * 7)
#endif
#ifndef ROM_ADDR
   #define ROM_ADDR (0)
#endif

/**
 * Initializes ROM
 */
void rom_init();

#endif
/**
 * Writes a character to an address that is otherwise inaccessible (for program setup)
 * 
 * addr - adddress to write to
 * data - data to write
 */
void write_rom_char(data_t addr, uint8_t data);


/**
 * Writes to an address that is otherwise inaccessible (for program setup)
 * 
 * addr - adddress to write to
 * data - data to write
 */
void write_rom(data_t addr, instr_t data);

#endif