#ifndef __REGS_H
#define __REGS_H

#include <stdint.h>

/**
 * Reads a value from a register
 * 
 * reg - register to read from
 * return - value in register reg
 */
uint32_t read_reg(uint8_t reg);

/**
 * Writes a value to a register
 * 
 * reg - register to write to
 * data - value to write
 */
void write_reg(uint8_t reg, uint32_t data);

/**
 * Flag types in flags
 */
enum flag_type {
    FLAG_CARRY = 0,
    FLAG_ZERO,
    FLAG_OVERFLOW,
    FLAG_NEG
};

/**
 * Reads a flag
 * 
 * flag - flag to read
 * return - the value of the flag.
 */
uint32_t read_flag(uint8_t flag);

/**
 * writes a specific value to a flag
 * 
 * flag - flag to write to
 * data - data to set the flag to
 */
void write_flag(uint8_t flag, uint8_t data);

/**
 * Retreives all flags
 * 
 * return - the flags integer
 */
uint32_t get_flags();

/**
 * Sets all flags
 * 
 * flags_in - flags to set
 */
void set_flags(uint32_t flags_in);

/**
 * Gets the current instruction address
 *
 * return - instruction pointer address
 */
uint32_t instruction_pointer();

/**
 * Sets the instruction pointer's address.
 * 
 * new_val - new instruction pointer
 */
void set_instruction_pointer(uint32_t new_val);
#endif
