#include <mem.h>
#include <stdio.h>
unsigned char rom[1024 * 4]; // 4k of ROM

unsigned char ram[1024 * 8]; // 8k of RAM

union int_to_char {
  unsigned int ic_val;
  unsigned char ic_char[4];
};


void write_mem(unsigned int addr, unsigned int val) {

  union int_to_char data;
  data.ic_val = val;

  for (int i = 0; i < 4; i++) {
    write_char_mem(addr + i, data.ic_char[i]);
  }
}

unsigned int read_mem(unsigned int addr) {
  union int_to_char data;

  for (int i = 0; i < 4; i++) {
    data.ic_char[i] = read_char_mem(addr + i);
  }
  return data.ic_val;
}

void write_char_mem(unsigned int addr, unsigned char val) {
  if (addr < ((1024 * 4) + (1024 * 8)) && addr > (1024 * 4)) {
    ram[(addr - (1024 * 4))] = val;
  } else {
    if (addr == 1024 * 16) {
      printf("%c", (char)val);
    }
  }
}

unsigned char read_char_mem(unsigned int addr) {
  if (addr < (1024 * 4)) {
    return rom[addr];
  } else if (addr < ((1024 * 4) + (1024 * 8))) {
    return rom[(addr - (1024 * 4))];
  }

  return 0;
}

void write_rom_char(unsigned int addr, unsigned char data) {
  rom[addr] = data;
}


void write_rom(unsigned int addr, unsigned int data) {
  union int_to_char conv;
  conv.ic_val = data;
  for (int i = 0; i < 4; i++) {
    write_rom_char(addr + i, conv.ic_char[i]);
  }
}
