#include <alu.h>
#include <stdio.h>


unsigned char alu_op_to_control(struct alu_op_type* val) {
  unsigned char out = val->alu_op_op;
  out |= (val->alu_op_carry_in & 0b1) << 3;
  out |= (val->alu_op_invert_b & 0b1) << 4;
  return out;
}


bit bit_alu(bit carry_in, bit a, bit b, unsigned char control) {
  control = control & 0b111;

  if (control == ALU_OP_ADD) {
    return add_bit(carry_in, a, b);
  } else if (control == ALU_OP_AND) {
    return and_bit(a, b);
  } else if(control == ALU_OP_OR) {
    return or_bit(a,b);
  } else if (control == ALU_OP_XOR) {
    return xor_bit(a,b);
  } else {
    printf("Unknown ALU OP: %d\n", control);
    return -1;
  }
}



void alu_op(bit* a, bit* b, int length, bit* out, unsigned char control, bit* carry, bit* overflow, bit* neg) {
  bit carry_in = (control >> 3) & 0b1;
  bit invert_b = (control >> 4) & 0b1;


  unsigned char control_data = control & 0b111;

  if (control_data == ALU_OP_ROR) {
    bit prev = *carry;
    for (int i = length - 1; i >= 0; i--) {
      out[i] = prev;
      prev = a[i];
    }
    *carry = prev;
  } else if (control_data == ALU_OP_ROL) {
    bit prev = *carry;
    for (int i = 0; i < length; i++) {
      out[i] = prev;
      prev = a[i];
    }
    *carry = prev;
  } else {
   bit val = 0;
   bit prev_carry = carry_in;
    for (int i = 0; i < length - 1; i++) {
      if (invert_b) {
        b[i] = (~b[i]) & 0b1;
      }
      bit val = bit_alu(carry_in, a[i], b[i], control);
      out[i] = val & 0b1;
      prev_carry = carry_in;
      carry_in = (val & 0b10) >> 1;
    }

    *overflow = (prev_carry ^ carry_in) & 0b1;
    *carry = carry_in;
  }

  *neg = b[length - 1] & 0b1;
}


bit add_bit(bit carry_in, bit a, bit b) {
  return (carry_in + a + b) & 0b11;
}

bit and_bit(bit a, bit b) {
  return (a & b) & 0b1;
}

bit or_bit(bit a, bit b) {
  return (a | b) & 0b1;
}

bit xor_bit(bit a, bit b) {
  return (a ^ b) & 0b1;;
}

union long_to_data {
  unsigned long data;
  unsigned int intdata[2];
  unsigned short shortdata[4];
  unsigned char chardata[8];
};

unsigned char bit_to_char(bit* arr) {
  unsigned long out = bit_to_num(arr, 8);

  union long_to_data d;
  d.data = out;
  return d.chardata[0];
}

void char_to_bit(unsigned char val, bit* out) {
  union long_to_data d;
  d.data = 0;
  d.chardata[0] = val;
  num_to_bit(d.data, out, 8);
}

unsigned short bit_to_short(bit* arr) {
  unsigned long out = bit_to_num(arr, 16);

  union long_to_data d;
  d.data = out;
  return d.shortdata[0];
}

void short_to_bit(unsigned short val, bit* out) {
  union long_to_data d;
  d.data = 0;
  d.shortdata[0] = val;
  num_to_bit(d.data, out, 16);
}

unsigned int bit_to_int(bit* arr) {
  unsigned long out = bit_to_num(arr, 32);

  union long_to_data d;
  d.data = out;
  return d.intdata[0];
}

void int_to_bit(unsigned int val, bit* out) {
  union long_to_data d;
  d.data = 0;
  d.intdata[0] = val;
  num_to_bit(d.data, out, 32);
}

void long_to_bit(unsigned long val, bit* out) {
  num_to_bit(val, out, 64);
}

unsigned long bit_to_long(bit* arr) {
  return bit_to_num(arr, 64);
}


void num_to_bit(unsigned long val, bit* out, int length) {
  for (int i = 0; i < length; i++) {
    out[i] = val & 0b1;
    val = val >> 1;
  }
}

unsigned long bit_to_num(bit* arr, int length) {
  unsigned long out = 0;
  for( int i = 0; i < length; i++) {
    out |= ((unsigned long)(arr[i] & 0b1) << i);
  }
  return out;
}

