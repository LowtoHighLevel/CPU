#include <alu.h>
#include <regs.h>
#include <stdio.h>
#include <defs.h>
#include <util.h>




/**
 * Runs an AND gate on two bits
 * 
 * a - first bit
 * b - second bit
 * return: a AND b
 */
bit and_bit(bit a, bit b) {
  return (a & b) & 0b1;
}


/**
 * Runs an OR gate on two bits
 * 
 * a - first bit
 * b - second bit
 * return: a OR b
 */
bit or_bit(bit a, bit b) {
  return (a | b) & 0b1;
}


/**
 * Runs an XOR gate on two bits
 * 
 * a - first bit
 * b - second bit
 * return: a XOR b
 */
bit xor_bit(bit a, bit b) {
  return (a ^ b) & 0b1;;
}

/**
 * Emulates a half adder
 * 
 * a - first input
 * b - Second input
 * return binary half added value
 */
bit half_add_bit(bit a, bit b) {
    bit hi = and_bit(a, b);
    bit lo = xor_bit(a, b);  
    return (hi << 1) | lo;
}

/**
 * Adds a single bit
 * 
 * carry_in - Carry input
 * a - A input
 * b - B input
 * return: a binary value with position 1 as the carry out, and position 0 as the output.
 */
bit add_bit(bit carry_in, bit a, bit b) {
  bit half = half_add_bit(a, b);
  bit full = half_add_bit(half & 0b1, carry_in);
  bit out = ((full | half) & 0b10) | (full & 0x1);
  return out;
}



/**
 * Handles an ALU for a single bit
 * 
 * carry_in - carry input
 * a - a input
 * b - b input
 * control - alu operation
 * return - the output of the alu operation
 */
bit bit_alu(bit carry_in, bit a, bit b, uint8_t control) {
  control = control & 0b111;

  switch (control) {
    case ALU_OP_ADD: return add_bit(carry_in, a, b);
    case ALU_OP_AND: return and_bit(a, b);
    case ALU_OP_OR: return or_bit(a, b);
    case ALU_OP_XOR: return xor_bit(a, b);
    default: {
      char buffer[100];
      sprintf(buffer, "Unknown ALU OP: %d\n", control);
      log_message(LOG_WARNING, buffer);
      return -1;
    }
  }
}

void alu_op(bit* a, bit* b, int length, bit* out, uint8_t control) {
  
  // Gather control data
  bit carry_in = (control >> 3) & 0b1; // Carry in
  bit invert_b = (control >> 4) & 0b1; // Whether we invert b (For subtraction)
  uint8_t operation = control & 0b111; // the actual operation


  // Handle operations
  switch (operation) {
    case ALU_OP_ROR: {
      bit carry = read_flag(FLAG_CARRY);
      for (int i = length - 1; i >= 0; i--) {
        out[i] = carry;
        carry = a[i];
      }
      write_flag(FLAG_CARRY, carry);
      break;
    }
    case ALU_OP_ROL: {
      bit carry = read_flag(FLAG_CARRY);
      for (int i = 0; i < length; i++) {
        out[i] = carry;
        carry = a[i];
      }
      write_flag(FLAG_CARRY, carry);
      break;
    }
    default: {
      bit val = 0; // output value
      bit prev_carry = carry_in; // carry from previous iteration
      
      // iterate through each bit and run an alu operation on it
      for (int i = 0; i < length; i++) {

        // Invert B
        if (invert_b) {
            b[i] = (~b[i]) & 0b1;
        }
        // Run the operation on current bit and set output, and carry
        bit val = bit_alu(carry_in, a[i], b[i], control);
        out[i] = val & 0b1;
        prev_carry = carry_in;
        carry_in = (val & 0b10) >> 1;
      }

      // Handle last-minute flags
      write_flag(FLAG_OVERFLOW, (prev_carry ^ carry_in) & 0b1);
      write_flag(FLAG_CARRY, carry_in);
      break;
    }
  }
  write_flag(FLAG_NEG, out[length-1]);
}

#ifdef TEST_ALU
#include <stdlib.h>
#ifndef TEST_ALU_BITLENGTH
#define TEST_ALU_BITLENGTH 32
#endif


/**
 * runs a specific alu function
 * 
 * x - first input
 * y - second input
 * control - alu control
 * return - output
 */
uint64_t testFn(uint64_t x, uint64_t y, uint8_t control) {

  bit a[TEST_ALU_BITLENGTH], b[TEST_ALU_BITLENGTH], c[TEST_ALU_BITLENGTH];
  num_to_bit(x, a, TEST_ALU_BITLENGTH);
  num_to_bit(y, b, TEST_ALU_BITLENGTH);
  alu_op(a, b, TEST_ALU_BITLENGTH, c, control);
  return bit_to_num(c, TEST_ALU_BITLENGTH);
}

/**
 * Masks a long into the right size
 * 
 * x - test value
 */
uint64_t mask_bits(uint64_t x) {
  return gen_mask(TEST_ALU_BITLENGTH) & x;
}

/**
 * tests a specific item and returns whether it worked or not
 * 
 * x - first input
 * y - second input
 * compare - a value to check against
 * control - alu control value
 * return - -1 if successful, out if not
 */
uint64_t test(uint64_t x, uint64_t y, uint64_t compare, uint8_t control) {
  uint64_t out = testFn(x, y, control);
  if (compare == out) {
    return -1;
  }
  return out;
}

/**
 * Tests like test() but prints an error and exits upon an error
 * 
 * x - first input
 * y - second input
 * compare - comparision value
 * control - control value
 * errMessage - error message string
 */
void testErr(uint64_t x, uint64_t y, uint64_t compare, uint8_t control, const char * errMessage) {
  uint64_t val = test(x, y, compare, control);
  if (val != -1) {
    char buffer[100];
    sprintf(buffer, "%s with x: %lu, y: %lu, got %lu", errMessage, x, y, val);
    log_message(LOG_ERROR, buffer);
  }
}

int main(int argc, char* argv[]) {
  log_message(LOG_INFO, "ALU Test program!");
  char bitlength_buf[32];
  sprintf(bitlength_buf, "bitlength: %d\n", TEST_ALU_BITLENGTH);
  log_message(LOG_DEBUG, bitlength_buf);

  const char * names[] = {"and", "or", "xor", "add"};
  
  const uint8_t control[] = {ALU_OP_AND, ALU_OP_OR, ALU_OP_XOR, ALU_OP_ADD};
  const char * errs[] = {"failed to and", "failed to or", "failed to xor", "failed to add"};
  
  uint32_t test_len = 4;

  for (uint32_t i = 0; i < test_len; i++) {
    for (uint64_t x = 0; x < (1000); x++) {
      for (uint64_t y = 0; y < (1000); y++) {
          const uint64_t compares[] = {mask_bits(x) & mask_bits(y), mask_bits(x) | mask_bits(y), mask_bits(x) ^ mask_bits(y), mask_bits(x) + mask_bits(y)};
            testErr(x, y, compares[i], control[i], errs[i]);
      }
    }
    char test_success_buf[100];
    sprintf(test_success_buf, "test: %s succeeded!\n", names[i]);
    log_message(LOG_INFO, test_success_buf);
  }

   for (uint64_t x = 0; x < (1000); x++) {
          write_flag(FLAG_CARRY, 0);
          bit a[TEST_ALU_BITLENGTH], b[TEST_ALU_BITLENGTH], c[TEST_ALU_BITLENGTH];
          num_to_bit(x, a, TEST_ALU_BITLENGTH);
          num_to_bit(0, b, TEST_ALU_BITLENGTH);
          alu_op(a, b, TEST_ALU_BITLENGTH, c, ALU_OP_ROR);
          uint64_t num = bit_to_num(c, TEST_ALU_BITLENGTH);
          if ( num != x >> 1) {
                char buffer[100];
                sprintf(buffer, "rotate right with x: %lu, got %lu, expected %lu", x, num, x >> 1);
                log_message(LOG_ERROR, buffer);
          }
    }
    log_message(LOG_INFO, "test: ror succeeded!\n");

    for (uint64_t x = 0; x < (1000); x++) {
          write_flag(FLAG_CARRY, 0);
          bit a[TEST_ALU_BITLENGTH], b[TEST_ALU_BITLENGTH], c[TEST_ALU_BITLENGTH];
          num_to_bit(x, a, TEST_ALU_BITLENGTH);
          num_to_bit(0, b, TEST_ALU_BITLENGTH);
          alu_op(a, b, TEST_ALU_BITLENGTH, c, ALU_OP_ROL);
          uint64_t num = bit_to_num(c, TEST_ALU_BITLENGTH);
          if ( num != x << 1) {
                char buffer[100];
                sprintf(buffer, "rotate left with x: %lu, got %lu, expected: %lu", x, num, x << 1);
                log_message(LOG_ERROR, buffer);
          }
    }
    log_message(LOG_INFO, "test: rol succeeded!\n");


}
#endif