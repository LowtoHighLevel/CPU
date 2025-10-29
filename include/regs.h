#ifndef __REGS_H
#define __REGS_H

unsigned int read_reg(unsigned char reg);

void write_reg(unsigned char reg, unsigned int data);

unsigned int read_flag(unsigned char flag);

void write_flag(unsigned char flag, unsigned int data);

unsigned int get_flags();

#define FLAG_CARRY 0
#define FLAG_ZERO 1
#define FLAG_OVERFLOW 2
#define FLAG_NEG 3

#endif
