#include <util.h>

/**
 * Splits a long into other forms of data based on its memory usage.
 */
union long_to_data {
  uint64_t data;
  uint32_t intdata[2];
  uint16_t shortdata[4];
  uint8_t chardata[8];
};


void num_to_bit(uint64_t val, bit* out, uint32_t length) {
  for (int i = 0; i < length; i++) {
    out[i] = val & 0b1;
    val = val >> 1;
  }
}

uint64_t bit_to_num(bit* arr, uint32_t length) {
  uint64_t out = 0;
  for( int i = 0; i < length; i++) {
    out |= ((uint64_t)(arr[i] & 0b1) << i);
  }
  return out;
}


uint8_t bit_to_char(bit* arr) {
  uint64_t out = bit_to_num(arr, 8);

  union long_to_data d;
  d.data = out;
  return d.chardata[0];
}

void char_to_bit(uint8_t val, bit* out) {
  union long_to_data d;
  d.data = 0;
  d.chardata[0] = val;
  num_to_bit(d.data, out, 8);
}

uint16_t bit_to_short(bit* arr) {
  uint64_t out = bit_to_num(arr, 16);

  union long_to_data d;
  d.data = out;
  return d.shortdata[0];
}

void short_to_bit(uint16_t val, bit* out) {
  union long_to_data d;
  d.data = 0;
  d.shortdata[0] = val;
  num_to_bit(d.data, out, 16);
}

uint32_t bit_to_int(bit* arr) {
  uint64_t out = bit_to_num(arr, 32);

  union long_to_data d;
  d.data = out;
  return d.intdata[0];
}

void int_to_bit(uint32_t val, bit* out) {
  union long_to_data d;
  d.data = 0;
  d.intdata[0] = val;
  num_to_bit(d.data, out, 32);
}

void long_to_bit(uint64_t val, bit* out) {
  num_to_bit(val, out, 64);
}

uint64_t bit_to_long(bit* arr) {
  return bit_to_num(arr, 64);
}

uint64_t gen_mask(uint8_t length) {
  uint64_t val = 0L;
  for (uint8_t i = 0; i < length; i++) {
    val |= ((uint64_t)1 << i);
  }
  return val;
}
