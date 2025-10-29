#include <regs.h>
#include <stdio.h>
#include <stdlib.h>


#define NUM_REGISTERS 32
uint32_t regs[NUM_REGISTERS - 1];

uint32_t flags;

uint32_t ip;

uint32_t read_reg(uint8_t reg) {
  
  if (reg >= NUM_REGISTERS) {
    printf("Attempted to read invalid register: %u", reg);
    exit(1);    
  }

  if (reg == 0) {
    return 0;
  } else {
    return regs[reg-1];
  }
  
}

void write_reg(uint8_t reg, uint32_t data) {
  
  if (reg >= NUM_REGISTERS) {
    printf("Attempted to write to invalid register: %u", reg);
    exit(1);    
  }
  
  if (reg == 0) {
    return;
  }

  regs[reg-1] = data;
}

uint32_t read_flag(uint8_t flag) {
  return (flags >> flag) & 0x1;
}

void write_flag(uint8_t flag, uint8_t data) {
    flags &= (0xFFFF & ((data & 0x1) << flag));
}

uint32_t get_flags() {
  return flags;
}

void set_flags(uint32_t flags_in) {
  flags = flags_in;
}

uint32_t instruction_pointer() {
  return ip;
}

void set_instruction_pointer(uint32_t new_val) {
  ip = new_val;
}