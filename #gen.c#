#include <stdio.h>

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

union int_to_char {
  unsigned int ival;
  unsigned char cval[4];
};


void write_next(unsigned char ** addr, unsigned int val) {
  union int_to_char conv;

  conv.ival = val;

  for (int i = 0; i < 4; i++) {
    (*addr)[i] = conv.cval[i];
  }

  *addr += 4;
}

int main(int argc, char * argv[]) {


  unsigned char buf[4096*4];
  unsigned char * addr = buf;
  
  unsigned int ld1    = gen_load(1, 16);
  unsigned int ld2    = gen_load(2, 15);
  unsigned int add123 = gen_reg(0b00000, 1, 2, 3);
  unsigned int mov34  = gen_reg(0b00000, 3, 0, 4);
  unsigned int ld1a   = gen_load(5, (1024*16));



  write_next(&addr, ld1);
  write_next(&addr, ld2);
  write_next(&addr, add123);
  write_next(&addr, mov34);
  write_next(&addr, ld1a);
  

  unsigned int write  = gen_write_mem(5, 6);

  char * hw = "Hello, World!\n";
  int idx = 0;

  while (hw[idx] != 0) {
    write_next(&addr, gen_load(6, ((unsigned int)hw[idx])));
    write_next(&addr, write);
    idx++;
  }

  unsigned int len = addr-buf;
  
  FILE* ptr;

  ptr = fopen("out.bin", "wb");

  fwrite(buf, len, 1, ptr);

  fclose(ptr);

  
  return 0;
  
  
}
