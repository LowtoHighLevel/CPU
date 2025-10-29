#ifndef __ALU_H
#define __ALU_H

#include <util.h>
#include <stdint.h>

/**
 * ALU Operation command type
 */
enum alu_op_type_cmd {
  ALU_OP_ADD = 0,
  ALU_OP_AND,
  ALU_OP_OR,
  ALU_OP_XOR,
  ALU_OP_ROR,
  ALU_OP_ROL
};

/**
 * ALU Operation types
 */
struct alu_op_type {
  bit alu_op_carry_in;
  bit alu_op_invert_b;
  uint8_t alu_op_op;
};

/**
 * Runs an ALU operation on arrays of bits.
 * a - Bit array for input A
 * b - Bit array for input B
 * length - Size of a, b, and out
 * out - Output bit array
 * control - Control data passed from CPU
 */
void alu_op(bit* a, bit* b, int length, bit* out, uint8_t control);

#endif
