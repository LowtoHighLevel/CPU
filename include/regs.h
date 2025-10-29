#ifndef __REGS_H
#define __REGS_H

unsigned int read_reg(unsigned char reg);

void write_reg(unsigned char reg, unsigned int data);

enum flag_type {
    FLAG_CARRY = 0,
    FLAG_ZERO,
    FLAG_OVERFLOW,
    FLAG_NEG
};

unsigned int read_flag(unsigned char flag);

void write_flag(unsigned char flag, unsigned int data);

unsigned int get_flags();

void set_flags(unsigned int flags_in);

#endif
