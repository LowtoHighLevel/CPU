#ifndef UTIL_H
#define UTIL_H
#include <stdint.h>

// BIT type
#define bit uint8_t

/**
 * Converts a bit array to a character
 * 
 * arr - input array
 * return - character
 */    
uint8_t bit_to_char(bit* arr);

/**
 * Converts a character to a bit array
 * 
 * val - character input
 * out - output array
 */
void char_to_bit(uint8_t val, bit* out);


/**
 * Converts a bit array to a short
 * 
 * arr - input array
 * return - short
 */    
uint16_t bit_to_short(bit* arr);


/**
 * Converts a short to a bit array
 * 
 * val - short input
 * out - output array
 */
void short_to_bit(uint16_t val, bit* out);


/**
 * Converts a bit array to an integer
 * 
 * arr - input array
 * return - integer
 */    
uint32_t bit_to_int(bit* arr);


/**
 * Converts a int to a bit array
 * 
 * val - int input
 * out - output array
 */
void int_to_bit(uint32_t val, bit* out);


/**
 * Converts a bit array to a long
 * 
 * arr - input array
 * return - long
 */    
uint64_t bit_to_long(bit* arr);

/**
 * Converts a long to a bit array
 * 
 * val - long input
 * out - output array
 */
void long_to_bit(uint64_t val, bit* out);


/**
 * Converts a number to a bit array
 * 
 * val - input value (assume long)
 * out - output array
 * length - bit size of number
 */
void num_to_bit(uint64_t val, bit* out, uint32_t length);

/**
 * Converts a bit array to a number
 * 
 * arr - input array
 * length - bit length of number
 * return: output value
 */
uint64_t bit_to_num(bit* arr, uint32_t length);

/**
 * Generates a bitmask of all 1s of length length
 * 
 * length - length of bitmask
 * return: all ones from 0..length
 */
uint64_t gen_mask(uint8_t length);

// Log types
enum LOG_TYPE {
    LOG_DEBUG=0,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
};

/**
 * Logs to stderr any information
 *
 * log_type - Log Level
 * message - Log message
 */
void log_message(uint8_t log_type, char * message);

#endif