#ifndef __ALU_H
#define __ALU_H

#define bit unsigned char


enum alu_op_type_cmd {
  ALU_OP_ADD = 0,
  ALU_OP_AND,
  ALU_OP_OR,
  ALU_OP_XOR,
  ALU_OP_ROR,
  ALU_OP_ROL
};

struct alu_op_type {
  bit alu_op_carry_in;
  bit alu_op_invert_b;
  unsigned char alu_op_op;
};

unsigned char alu_op_to_control(struct alu_op_type* val);

void alu_op(bit* a, bit* b, int length, bit* out, unsigned char control, bit* carry, bit* overflow, bit* neg);

bit bit_alu(bit carry_in, bit a, bit b, unsigned char control);

bit add_bit(bit carry_in, bit a, bit b);

bit and_bit(bit a, bit b);

bit or_bit(bit a, bit b);

bit xor_bit(bit a, bit b);

bit ror_bit(bit a, bit b);

bit rol_bit(bit a, bit b);

unsigned char bit_to_char(bit* arr);

void char_to_bit(unsigned char val, bit* out);

unsigned short bit_to_short(bit* arr);

void short_to_bit(unsigned short val, bit* out);

unsigned int bit_to_int(bit* arr);

void int_to_bit(unsigned int val, bit* out);

unsigned long bit_to_long(bit* arr);

void long_to_bit(unsigned long val, bit* out);

void num_to_bit(unsigned long val, bit* out, int length);

unsigned long bit_to_num(bit* arr, int length);

#endif
