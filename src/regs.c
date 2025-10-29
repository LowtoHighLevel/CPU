#include <regs.h>

unsigned int regs[31];

unsigned int flags;

unsigned int read_reg(unsigned char reg) {
  if (reg == 0) {
    return 0;
  } else {
    return regs[reg-1];
  }
  
}

void write_reg(unsigned char reg, unsigned int data) {
  if (reg == 0) {
    return;
  }

  regs[reg-1] = data;
}

unsigned int read_flag(unsigned char flag) {
  return (flags >> flag) & 0x1;
}

void write_flag(unsigned char flag, unsigned int data) {
    flags &= (0xFFFF & ((data & 0x1) << flag));
}

unsigned int get_flags() {
  return flags;
}
