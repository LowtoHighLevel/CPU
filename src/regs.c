#include <regs.h>
#include <stdio.h>
#include <stdlib.h>
#include <defs.h>
#include <util.h>

#define NUM_REGISTERS 32
data_t regs[NUM_REGISTERS - 1];

uint32_t flags;

void reg_out_bounds(const char* type, uint8_t reg) {
  if (reg >= NUM_REGISTERS) {
    char buf[100];
    sprintf(buf, "Attempted to %s invalid register: %u", type, reg);
    log_message(LOG_ERROR, buf);
  }
}
data_t read_reg(uint8_t reg) {
  
  reg_out_bounds("read", reg);

  if (reg == 0) {
    return 0;
  } else {
    return regs[reg-1];
  }
  
}

void write_reg(uint8_t reg, data_t data) {
  reg_out_bounds("write", reg);
  
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

data_t instruction_pointer() {
  return regs[30];
}

void set_instruction_pointer(data_t new_val) {
  regs[30] = new_val;
}