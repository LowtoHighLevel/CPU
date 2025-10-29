#include <stdio.h>
#include <cpu.h>
#include <regs.h>
#include <alu.h>
#include <mem.h>

void read_op(unsigned int addr, unsigned int* cmd) {
  *cmd = read_mem(addr);
}

void parse_op(unsigned int op, unsigned char * typ, unsigned char* control, unsigned char* reg1, unsigned char* reg2, unsigned char* reg3, unsigned int* imm) {

  *typ = (unsigned char)((op >> 29) & 0b111);
  if (*typ == 0) {
    *control = (unsigned char)((op >> 24) & 0b11111);
    *reg1 = (unsigned char)((op >> 16) & 0xFF);
    *reg2 = (unsigned char)((op >> 8) & 0xFF);
    *reg3 = (unsigned char)((op >> 0) & 0xFF);
    *imm = 0;
  } else if (*typ == 1) {
    *reg3 = (unsigned char)((op >> 24) & 0b11111);
    *imm = (unsigned int) op & 0xFFFFFF;
    *reg1 = 0;
    *reg2 = 0;
    *control = 0;
  } else if (*typ == 2) {
    *control = 0;
    *reg1 = (unsigned char)((op >> 16) & 0xFF);
    *reg2 = 0;
    *reg3 = (unsigned char)((op) & 0xFF);
    *imm = 0;
  } else if (*typ == 3) {
    *control = 0;
    *reg1 = (unsigned char)((op >> 16) & 0xFF);
    *reg2 = (unsigned char)((op >> 8) & 0xFF);
    *reg3 = 0;
    *imm = 0;
  } else {
    *control =  (unsigned char)((op >> 24) & 0b11111);
    *reg1 = 0;
    *reg2 = 0;
    *reg3 = 0;
    *imm = 0;
  }
}

void read_data(unsigned char reg1, unsigned char reg2, unsigned int * d1, unsigned int * d2) {
  *d1 = read_reg(reg1);
  *d2 = read_reg(reg2);
}

void aluop(unsigned int x, unsigned int y, unsigned char control, unsigned int * out) {
  bit a[32];
  bit b[32];
  bit c[32];

  int_to_bit(x, a);
  int_to_bit(y, b);

  alu_op(a, b, 32, c, control);



  *out = bit_to_int(c);
  write_flag(FLAG_ZERO, *out == 0);
}

void write_back(unsigned char reg, unsigned int data) {
  write_reg(reg, data);
}

unsigned char condition(unsigned char control) {
  return (
	  (control == 0) ||
	  (control == 1 && read_flag(FLAG_ZERO)) ||
	  (control == 2 && read_flag(FLAG_CARRY)) ||
	  (control == 3 && read_flag(FLAG_OVERFLOW)) ||
	  (control == 4 && read_flag(FLAG_NEG))
	  );
}

union short_ushort {
  short s;
  unsigned short us;
};

union int_uint {
  int i;
  unsigned int ui;
};

void run_cmd(unsigned int * addr) {

  unsigned int cmd = 0;
  read_op(*addr, &cmd);
  unsigned char typ, control, reg1, reg2, reg3;
  unsigned int imm;
  parse_op(cmd, &typ, &control, &reg1, &reg2, &reg3, &imm);
  unsigned int d1, d2, d3;
  read_data(reg1, reg2, &d1, &d2);

  union short_ushort rel;
  rel.us = (cmd & 0xFFFF);
  unsigned char check = condition(control);

  if (typ >= 0b100) {
    if (typ == 0b100 && check) {
      union int_uint iui;
      
      iui.ui = *addr;
      iui.i += (rel.s * 4);
      *addr = iui.ui;
    } else if (typ == 0b101 && check) {
      *addr = d1;
    } else {
      *addr += 4;
    }
  } else {
     aluop(d1, d2, control, &d3);
     
     if (typ == 0b000) {
       write_back(reg3, d3);
     } else if (typ == 0b001) {
       write_back(reg3, imm);
     } else if (typ == 0b010) {
       d3 = read_mem(d1);
       write_back(reg3, d3);
     } else if (typ == 0b011) {
       write_mem(d1, d2);
     }
     
     *addr += 4;
   }
}
