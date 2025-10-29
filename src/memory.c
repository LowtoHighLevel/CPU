#include <mem.h>
#include <stdio.h>

#define ROM_SIZE 1024 * 4
#define RAM_SIZE 1024 * 8

#define ROM_ADDR 0
#define RAM_ADDR ROM_ADDR + ROM_SIZE
#define CHAROUT_ADDR 1024 * 16

unsigned char rom[ROM_SIZE]; // 4k of ROM
unsigned char ram[RAM_SIZE]; // 8k of RAM

unsigned char scan_val;

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
  if (addr < (RAM_ADDR + RAM_SIZE) && addr >= RAM_ADDR) {
    ram[(addr - RAM_ADDR)] = val;
  } else if (addr == CHAROUT_ADDR) {
    printf("%c", (char)val);
  }
}   

unsigned char read_char_mem(unsigned int addr) {
  if (addr < (ROM_SIZE) && addr >= ROM_ADDR) {
    return rom[addr];
  } else if (addr < (RAM_ADDR + RAM_SIZE) && addr >= RAM_ADDR) {
    return ram[(addr - (RAM_ADDR))];
  } else if (addr == CHAROUT_ADDR) {
    scanf("%c", &scan_val);
    return scan_val;
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
