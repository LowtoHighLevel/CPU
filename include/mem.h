#ifndef __MEM_H
#define __MEM_H


/**
 * Writes a value to an address
 * 
 * addr - Address to write to
 * val - Value to write at address
 */
void write_mem(unsigned int addr, unsigned int val);

/**
 * Reads from memory at an address
 * 
 * addr - address to read from
 * return - memory at addr.
 */
unsigned int read_mem(unsigned int addr);

/**
 * Writes a char at an address.
 * 
 * addr - Address to write to
 * val - value to write
 */
void write_char_mem(unsigned int addr, unsigned char val);

/**
 * Reads a character from memory
 * 
 * addr - address to read from
 * return - the character at address addr
 */
unsigned char read_char_mem(unsigned int addr);

/**
 * Writes a character to an address that is otherwise inaccessible (for program setup)
 * 
 * addr - adddress to write to
 * data - data to write
 */
void write_rom_char(unsigned int addr, unsigned char data);


/**
 * Writes to an address that is otherwise inaccessible (for program setup)
 * 
 * addr - adddress to write to
 * data - data to write
 */
void write_rom(unsigned int addr, unsigned int data);
#endif
