#include <stdio.h>
#include <cpu.h>
#include <regs.h>
#include <mem.h>


void print_binary(unsigned int val) {
  for (int i = 31; i >= 0; i--) {
    printf("%u", (val >> i) & 0b1);
  }
}

unsigned int gen_load(unsigned char reg, unsigned int val) {
  unsigned int out = 0b001 << 29;
  out |= (((unsigned int)reg) << 24);
  out |= (val & 0xFFFFFF);
  return out;
}

unsigned int gen_reg(unsigned char control, unsigned char r1, unsigned char r2, unsigned char r3) {
  unsigned int out = 0;
  out |= (((unsigned int)control) << 24);
  out |= ((unsigned int)r1) << 16;
  out |= ((unsigned int)r2) << 8;
  out |= ((unsigned int)r3);
  return out;
}

unsigned int gen_read_mem(unsigned char r1, unsigned char r3) {
  unsigned int out = 0b010 << 29;
  out |= ((unsigned int)r1) << 16;
  out |= ((unsigned int)r3);
  return out;
}

unsigned int gen_write_mem(unsigned char r1, unsigned char r2) {
  unsigned int out = 0b011 << 29;
  out |= ((unsigned int)r1) << 16;
  out |= ((unsigned int)r2) << 8;
  return out;
}

unsigned int jmprel(unsigned char condition, short rel) {
  unsigned int out = 0b100 << 29;
  out |= (((unsigned int)condition) << 24);
  out |= (unsigned int)rel;
  return out;
}

unsigned int jmpreg(unsigned char condition, unsigned char reg) {
  unsigned int out = 0b101 << 29;
  out |= (((unsigned int)condition) << 24);
  out |= ((unsigned int)reg) << 16;
  return out;
}

void write_next(unsigned int * addr, unsigned int val) {
  write_rom(*addr, val);
  *addr += 4;
}


int main(int argc, char * argv[]) {
  unsigned char carry = 0, zero = 0, overflow = 0, neg = 0;

  unsigned int addr = 0;
  
  unsigned int ld1    = gen_load(1, 16);
  unsigned int ld2    = gen_load(2, 15);
  unsigned int add123 = gen_reg(0b00000, 1, 2, 3);
  unsigned int mov34  = gen_reg(0b00000, 3, 0, 4);
  unsigned int ld1a   = gen_load(5, (1024*16));
  unsigned int ld2a   = gen_load(6, ((unsigned int)'h'));
  unsigned int write  = gen_write_mem(5, 6);
  unsigned int ld2b   = gen_load(6, ((unsigned int)'\n'));

  
  write_next(&addr, ld1);
  write_next(&addr, ld2);
  write_next(&addr, add123);
  write_next(&addr, mov34);
  write_next(&addr, ld1a);
  write_next(&addr, ld2a);
  write_next(&addr, write);
  write_next(&addr, ld2b);
  write_next(&addr, write);

  addr = 0;
  for (int i = 0; i < 9; i++) {
    run_cmd(&addr, &carry, &zero, &overflow, &neg);
  }
  
  printf("Registers: \n");
  for (int i = 0; i < 32; i++) {
    printf("reg%d: %u\n", i, read_reg(i));
  }
  printf("\n)");
}

