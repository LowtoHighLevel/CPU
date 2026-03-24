#include <mem.h>
#include <stdio.h>
#include <defs.h>
#include <stdint.h>
#include <util.h>

#define ROM
#define RAM
#define CHARDEV

#ifdef ROM
 #ifndef ROM_SIZE
  #define ROM_SIZE (1024 * 7)
 #endif
 #ifndef ROM_ADDR
  #define ROM_ADDR (0)
 #endif
unsigned char rom[ROM_SIZE];
#endif

#ifdef RAM
 #ifndef RAM_SIZE
  #define RAM_SIZE (1024 * 8)
 #endif
 #ifndef RAM_ADDR
  #ifdef ROM
    #define RAM_ADDR (ROM_ADDR + ROM_SIZE)
  #else
    #define RAM_ADDR (0)
  #endif
 #endif
unsigned char ram[RAM_SIZE];
#endif

#ifdef CHARDEV
  #ifndef CHARDEV_ADDR
    #define CHARDEV_ADDR (1024 * 16)
  #endif
#endif

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

  for (int i = 0; i < sizeof(data_t); i++) {
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
  #ifdef RAM
  if (addr < (RAM_ADDR + RAM_SIZE) && addr >= RAM_ADDR) {
    ram[addr - RAM_ADDR] = val;
  }
  #endif

  #ifdef CHARDEV
  else if (addr == CHARDEV_ADDR) {
    // Actual output, not a log
    printf("%c", (char)val);
  }
  #endif
}   

uint8_t read_char_mem(data_t addr) {

  #ifdef ROM
  if (addr < (ROM_SIZE + ROM_ADDR) && addr >= ROM_ADDR) {
    return rom[addr - ROM_ADDR];
  } else
  #endif
  #ifdef RAM
  if (addr < (RAM_ADDR + RAM_SIZE) && addr >= RAM_ADDR) {
    return ram[addr - RAM_ADDR];
  } else
  #endif
  #ifdef CHARDEV
  if (addr == (CHARDEV_ADDR)) {
    char ch;
    scanf("%c", &ch);
    return (uint8_t) ch;
  #endif

  return 0;
}


void write_rom_char(data_t addr, uint8_t data) {
  #ifdef ROM
    rom[addr] = data;
  #endif
}

void write_rom(data_t addr, instr_t data) {
  union int_to_char conv;
  conv.ic_val = data;
  for (int i = 0; i < sizeof(instr_t); i++) {
    write_rom_char(addr + i, conv.ic_char[i]);
  }
}

