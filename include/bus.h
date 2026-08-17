#ifndef __BUS_H
#define __BUS_H

#include <defs.h>
#include <stdint.h>


/**
 * Bus Device
 */
typedef struct bus_dev_t {
    data_t address;
    size_t length;
    void (*write_char)(size_t offset, uint8_t val);
    uint8_t (*read_char)(size_t offset);
} BUS_DEV;

/**
 * Registers a bus device
 * 
 * dev - Bus device to register
 * returns - index to device
 */
int register_bus_device(BUS_DEV* dev);

/**
 * Unregisters a bus device
 * 
 * idx - index of device.
 */
int unregister_bus_device(int idx);

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

#endif
