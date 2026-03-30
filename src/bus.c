#include <bus.h>
#include <stdio.h>
#include <defs.h>
#include <stdint.h>
#include <util.h>

//#define DEV_ROM
//#define DEV_RAM
//#define DEV_CHAR

#ifdef DEV_ROM
 #ifndef ROM_SIZE
  #define ROM_SIZE (1024 * 7)
 #endif
 #ifndef ROM_ADDR
  #define ROM_ADDR (0)
 #endif
unsigned char rom[ROM_SIZE];
#endif

#ifdef DEV_RAM
 #ifndef RAM_SIZE
  #define RAM_SIZE (1024 * 8)
 #endif
 #ifndef RAM_ADDR
  #ifdef DEV_ROM
    #define RAM_ADDR (ROM_ADDR + ROM_SIZE)
  #else
    #define RAM_ADDR (0)
  #endif
 #endif
unsigned char ram[RAM_SIZE];
#endif

#ifdef DEV_CHAR
  #ifndef DEV_CHAR_ADDR
    #define DEV_CHAR_ADDR (1024 * 16)
  #endif
#endif
BUS_DEV* devices[128];

int register_bus_device(BUS_DEV* dev) {
  size_t idx = 0;
  while (devices[idx] != 0) {
    idx++;
  }
  devices[idx] = dev;
  return idx;
}

int unregister_bus_device(int idx) {
  if ((idx >= 128 && idx < 0) || devices[idx] == 0) return -1;
  devices[idx] = 0;
  return 0;
}

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
  #ifdef DEV_RAM
  if (addr < (RAM_ADDR + RAM_SIZE) && addr >= RAM_ADDR) {
    ram[addr - RAM_ADDR] = val;
  }
  #endif

  #ifdef DEV_CHAR
  else if (addr == DEV_CHAR_ADDR) {
    // Actual output, not a log
    printf("%c", (char)val);
  }
  #endif
}   

uint8_t read_char_mem(data_t addr) {

  #ifdef DEV_ROM
  if (addr < (ROM_SIZE + ROM_ADDR) && addr >= ROM_ADDR) {
    return rom[addr - ROM_ADDR];
  } else
  #endif
  #ifdef DEV_RAM
  if (addr < (RAM_ADDR + RAM_SIZE) && addr >= RAM_ADDR) {
    return ram[addr - RAM_ADDR];
  } else
  #endif
  #ifdef DEV_CHAR
  if (addr == (DEV_CHAR_ADDR)) {
    char ch;
    scanf("%c", &ch);
    return (uint8_t) ch;
  }
  #endif

  return 0;
}


void write_rom_char(data_t addr, uint8_t data) {
  #ifdef DEV_ROM
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

