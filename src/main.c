#include <stdio.h>
#include <cpu.h>
#include <regs.h>
#include <mem.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * Write a value to rom and iter the address.
 */
void write_next(uint32_t * addr, uint32_t val) {
  write_rom(*addr, val);
  *addr += 4;
}

/**
 * Main program
 * argv[1] - Program file
 */
int main(int argc, char * argv[]) {

  // Current address in program
  uint32_t addr = 0;


  
  uint8_t print_registers = 0;
  uint8_t input_type = 0;
  int input_file_i = 0;
  if (argc > 2) {
    for (int i = 2; i < argc; i++) {
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

  if (input_type == 1) {
    // Try and open a binary file
    FILE* ptr = fopen(argv[input_file_i],"rb");
    if (ptr == NULL) {
      printf("No such file.\n");
      return 1;
    }

    // Store program in temporary ram
    uint32_t cmds[4096];
    int32_t num_cmds = fread(cmds, sizeof(uint8_t), 4096, ptr);
    fclose(ptr);

    // write program to ROM.
    for (int32_t i = 0; i < num_cmds; i++) {
      write_next(&addr, cmds[i]);
    }
  } else if (input_type == 2) {
    uint32_t cmds[4096];
    int32_t num_cmds = argc - input_file_i;
    for (int i = input_file_i; i < argv; i++) {
      cmds[i-input_file_i] = (int)strtol(argv[i], NULL, 16);
    }
    for (int32_t i = 0; i < num_cmds; i++) {
      write_next(&addr, cmds[i]);
    }

  } else {
    // Store program in temporary ram
    uint32_t cmds[4096];
    int32_t num_cmds = fread(cmds, sizeof(uint8_t), 4096, stdin);

    // write program to ROM.
    for (int32_t i = 0; i < num_cmds; i++) {
      write_next(&addr, cmds[i]);
    }
  }

  init();
  // run main program (setting r30 to 36000 is a hack to exit. TODO: make it better :))
  while (read_reg(30) != 36000) {
      run_cmd();
  }

  // print out registers at end if needed.
  if (argc > 2 && strcmp(argv[2], "-r") == 0) {
    printf("Registers: \n");
    for (uint8_t i = 0; i < 32; i++) {
      printf("reg%d: %u\n", i, read_reg(i));
    }
    printf("\n)");
  }

  return 0;
}

