#ifndef __MEM_H
#define __MEM_H

#include <defs.h>
#include <stdint.h>

/**
 * Writes a value to an address
 * 
 * addr - Address to write to
 * val - Value to write at address
 */
void write_mem(data_t addr, data_t val);

/**
 * Reads an instruction from memory
 * 
 * addr - address of instruction
 * val - Value at the instruction address.
 * return - An instruction
 */
instr_t read_instruction(data_t addr);

/**
 * Reads from memory at an address
 * 
 * addr - address to read from
 * return - memory at addr.
 */
data_t read_mem(data_t addr);

/**
 * Writes a char at an address.
 * 
 * addr - Address to write to
 * val - value to write
 */
void write_char_mem(data_t addr, uint8_t val);

/**
 * Reads a character from memory
 * 
 * addr - address to read from
 * return - the character at address addr
 */
uint8_t read_char_mem(data_t addr);

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
