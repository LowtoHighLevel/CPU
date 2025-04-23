#include <regs.h>

unsigned int regs[31];

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
