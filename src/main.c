#include <stdio.h>
#include <defs.h>
#include <cpu.h>
#include <regs.h>
#include <mem.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * Write a value to rom and iter the address.
 */
void write_next(data_t * addr, data_t val) {
  write_rom(*addr, val);
  *addr += 4;
}

/**
 * Main program
 * argv[1] - Program file
 */
int main(int argc, char * argv[]) {

  // Current address in program
  data_t addr = 0;
  
  uint8_t print_registers = 0;
  uint8_t input_type = 0;
  int input_file_i = 0;
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-r") == 0) {
        print_registers = 1;
      } else if (strcmp(argv[i], "-b") == 0) {
        input_type = 2;
        input_file_i = ++i;
        break;
      } else if (strcmp(argv[i], "-f") == 0) {
        input_type = 1;
        input_file_i = ++i;
      }
    }
  }


  instr_t cmds[4096];
  int32_t num_cmds = 0;

  if (input_type == 1) {
    printf("Loading file: %s\n", argv[input_file_i]);
    // Try and open a binary file
    FILE* ptr = fopen(argv[input_file_i],"rb");
    if (ptr == NULL) {
      printf("No such file.\n");
      return 1;
    }

    // Store program in temporary ram
    num_cmds = fread(cmds, sizeof(uint8_t), 4096, ptr);
    fclose(ptr);

    // write program to ROM.
    
  } else if (input_type == 2) {
    num_cmds = argc - input_file_i;
    for (int i = input_file_i; i < argc; i++) {
      cmds[i-input_file_i] = (int)strtol(argv[i], NULL, 16);
    }

  } else {
    // Store program in temporary ram
    num_cmds = fread(cmds, sizeof(uint8_t), 4096, stdin);
  }

  for (int32_t i = 0; i < num_cmds; i++) {
    write_next(&addr, cmds[i]);
  }

  init();
  // run main program (setting r30 to 36000 is a hack to exit. TODO: make it better :))
  while (read_reg(30) != 36000) {
      run_cmd();
  }

  // print out registers at end if needed.
  if (print_registers) {
    printf("Registers: \n");
    for (uint8_t i = 0; i < 32; i++) {
      printf("reg%d: %u\n", i, read_reg(i));
    }
    printf("\n)");
  }

  return 0;
}

