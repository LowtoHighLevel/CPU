#include <stdio.h>
#include <cpu.h>
#include <defs.h>
#include <regs.h>
#include <alu.h>
#include <mem.h>
#include <util.h>

/**
 * Reads an instruction from memory
 * 
 * addr - memory address
 * cmd - pointer to instruction
 */
void read_op(data_t addr, instr_t* cmd) {
  *cmd = read_instruction(addr);
}

/**
 * Parses a cpu instruction and breaks it out into different registers, control bits, or an immidiate value.
 * 
 * op - cpu instruction
 * typ - pointer to instruction type
 * control - pointer to control value
 * reg1-3 - pointers to register numbers
 * imm - pointer to immediate value
 */
void parse_op(instr_t op, uint8_t* typ, uint8_t* control, uint8_t* reg1, uint8_t* reg2, uint8_t* reg3, data_t* imm) {

  *typ = (uint8_t)((op >> CPU_OP_TYPE_POS) & 0b111);
  switch (*typ) {
    case CPU_TYPE_REGISTER: {
      *control = (uint8_t)((op >> 24) & 0b11111);
      *reg1 = (uint8_t)((op >> 16) & 0xFF);
      *reg2 = (uint8_t)((op >> 8) & 0xFF);
      *reg3 = (uint8_t)((op >> 0) & 0xFF);
      *imm = 0;
      break;
    }
    case CPU_TYPE_IMM: {
      *control = 0;
      *reg1 = 0;
      *reg2 = 0;
      *reg3 = (uint8_t)((op >> 24) & 0b11111);
      *imm = (op & 0xFFFFFF);
      break;
    }
    case CPU_TYPE_MEM_READ: {
      *control = 0;
      *reg1 = (uint8_t)((op >> 16) & 0xFF);
      *reg2 = 0;
      *reg3 = (uint8_t)((op) & 0xFF);
      *imm = 0;
      break;
    }
    case CPU_TYPE_MEM_WRITE: {
      *control = 0;
      *reg1 = (uint8_t)((op >> 16) & 0xFF);
      *reg2 = (uint8_t)((op >> 8) & 0xFF);
      *reg3 = 0;
      *imm = 0;
      break;
    } 
    default: {
      *control =  (uint8_t)((op >> CPU_OP_CONTROL_POS) & 0b11111);
      *reg1 = 0;
      *reg2 = 0;
      *reg3 = 0;
      *imm = 0;
      break;
    }
  }
}

/**
 * Reags data from a register and loads it into the values
 * 
 * reg1 - first register
 * reg2 - second register
 * d1 - pointer to store register 1 data
 * d2 - pointer to store regisger 2 data
 */
void read_data(uint8_t reg1, uint8_t reg2, data_t * d1, data_t * d2) {
  *d1 = read_reg(reg1);
  *d2 = read_reg(reg2);
}

/**
 * Calls an ALU operation
 * 
 * x - a input
 * y - b input
 * control - control data
 * out - output value
 */
void aluop(data_t x, data_t y, uint8_t control, data_t * out) {
  bit a[DATA_WIDTH], b[DATA_WIDTH], c[DATA_WIDTH];

  int_to_bit(x, a);
  int_to_bit(y, b);

  alu_op(a, b, DATA_WIDTH, c, control);

  *out = bit_to_int(c);
  write_flag(FLAG_ZERO, *out == 0);
}

/**
 * Writes back some data to a register
 */
void write_back(uint8_t reg, data_t data) {
  write_reg(reg, data);
}

/**
 * sanity checks control values for the cpu with the cpu's flags
 * 
 * control - control value from instruction
 * return - 1 if checks pass, 0 otherwise
 */
uint8_t condition(uint8_t control) {
  return (
	  (control == 0) ||
	  (control == 1 && read_flag(FLAG_ZERO)) ||
	  (control == 2 && read_flag(FLAG_CARRY)) ||
	  (control == 3 && read_flag(FLAG_OVERFLOW)) ||
	  (control == 4 && read_flag(FLAG_NEG))
	  );
}

/**
 * Converts a short to an unsigned short
 */
union short_ushort {
  int16_t s;
  uint16_t us;
};

/**
 * Converts an int to an unsigned int
 */
union int_uint {
  int32_t i;
  uint32_t ui;
};

void init() {
  set_flags(0);

  for (int i = 0; i < 32; i++) {
    write_reg(i, 0);
  }
  set_instruction_pointer(0);
}

void run_cmd() {
  // Load the instruction and parse it
  instr_t cmd = 0;
  read_op(instruction_pointer(), &cmd);
 // printf("ip: %x, cmd: %x\n", instruction_pointer(), cmd);
  uint8_t typ, control, reg1, reg2, reg3;
  data_t imm;
  parse_op(cmd, &typ, &control, &reg1, &reg2, &reg3, &imm);

  // Read any registers that are needed
  data_t d1, d2, d3;
  read_data(reg1, reg2, &d1, &d2);

  // Get relative address
  union short_ushort rel;
  rel.us = (cmd & 0xFFFF);

  // Check for jumps
  uint8_t check = condition(control);
  if (typ >= CPU_TYPE_JMP_REL) {
    // Relative jump
    if (typ == CPU_TYPE_JMP_REL && check) {
      union int_uint iui;
      
      iui.ui = instruction_pointer();
      iui.i += (rel.s * 4);
      set_instruction_pointer(iui.ui);
    }
    // jump to address in register
    else if (typ == CPU_TYPE_JMP_REG && check) {
      set_instruction_pointer(d1);
    }
    // jump to next instruction
    else {
      set_instruction_pointer(instruction_pointer() + 4);
    }
  }
  // not a jump instruction. Probably memory or ALU
  else {
     aluop(d1, d2, control, &d3);
     
     // handle output
     switch (typ) {
      case CPU_TYPE_REGISTER: write_back(reg3, d3); break;
      case CPU_TYPE_IMM: write_back(reg3, imm); break;
      case CPU_TYPE_MEM_READ: {
        d3 = read_mem(d1);
        write_back(reg3, d3);
        break;
      }
      case CPU_TYPE_MEM_WRITE: write_mem(d1, d2); break;
    }
    // go to next instruction
      set_instruction_pointer(instruction_pointer() + 4);
   }
}
