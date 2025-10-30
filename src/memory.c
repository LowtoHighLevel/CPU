#include <mem.h>
#include <stdio.h>
#include <defs.h>
#include <stdint.h>

#ifndef LAYOUT
#define LAYOUT 0
#endif

#if LAYOUT == 1
  #define ROM_SIZE 1024 * 2
  #define RAM_SIZE 1024 * 8
  #define ROM_ADDR STARTVEC - ROM_SIZE + 4
  #define RAM_ADDR 0
  #define CHAROUT_ADDR RAM_ADDR + RAM_SIZE
 
#else
  #define ROM_SIZE 1024 * 4
  #define RAM_SIZE 1024 * 8
  #define ROM_ADDR 0
  #define RAM_ADDR ROM_ADDR + ROM_SIZE
  #define CHAROUT_ADDR 1024 * 16

#endif


unsigned char rom[ROM_SIZE];
unsigned char ram[RAM_SIZE];

unsigned char scan_val;

union int_to_char {
  data_t ic_val;
  uint8_t ic_char[sizeof(data_t)];
};

union instr_to_char {
  instr_t ic_val;
  uint8_t ic_char[sizeof(instr_t)];
};


void write_mem(data_t addr, data_t val) {

  union int_to_char data;
  data.ic_val = val;

  for (int i = 0; i < 4; i++) {
    write_char_mem(addr + i, data.ic_char[i]);
  }
}

instr_t read_instruction(data_t addr) {
  union instr_to_char data;

  for (int i = 0 ; i < sizeof(instr_t); i++) {
    data.ic_char[i] = read_char_mem(addr + i);
  }
  return data.ic_val;
}

data_t read_mem(data_t addr) {
  union int_to_char data;

  for (int i = 0; i < sizeof(data_t); i++) {
    data.ic_char[i] = read_char_mem(addr + i);
  }
  return data.ic_val;
}

void write_char_mem(data_t addr, uint8_t val) {
  if (addr < (RAM_ADDR + RAM_SIZE) && addr >= RAM_ADDR) {
    ram[(addr - RAM_ADDR)] = val;
  }
  #if LAYOUT == 0
  else if (addr == CHAROUT_ADDR) {
    // Actual output, not a log
    printf("%c", (char)val);
  }
  #endif
}   

unsigned char read_char_mem(data_t addr) {


  if (addr < (ROM_SIZE) && addr >= ROM_ADDR) {
    return rom[addr];
  } else if (addr < (RAM_ADDR + RAM_SIZE) && addr >= RAM_ADDR) {
    return ram[(addr - (RAM_ADDR))];
  }

  return 0;
}

void write_rom_char(data_t addr, uint8_t data) {
  rom[addr] = data;
}

void write_rom(data_t addr, instr_t data) {
  union int_to_char conv;
  conv.ic_val = data;
  for (int i = 0; i < sizeof(instr_t); i++) {
    write_rom_char(addr + i, conv.ic_char[i]);
  }
}
