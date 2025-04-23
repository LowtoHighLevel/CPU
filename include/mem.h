#ifndef __MEM_H
#define __MEM_H


void write_mem(unsigned int addr, unsigned int val);

unsigned int read_mem(unsigned int addr);

void write_char_mem(unsigned int addr, unsigned char val);

unsigned char read_char_mem(unsigned int addr);

void write_rom_char(unsigned int addr, unsigned char data);

void write_rom(unsigned int addr, unsigned int data);
#endif
