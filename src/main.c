#include <stdio.h>
#include <cpu.h>
#include <regs.h>
#include <mem.h>
#include <string.h>

/**
 * Write a value to rom and iter the address.
 */
void write_next(unsigned int * addr, unsigned int val) {
  write_rom(*addr, val);
  *addr += 4;
}


/**
 * Main program
 * argv[1] - Program file
 */
int main(int argc, char * argv[]) {

  // Current address in program
  unsigned int addr = 0;

  // Try and open a binary file
  FILE* ptr = fopen(argv[1],"rb");
  if (ptr == NULL) {
    printf("No such file.\n");
    return 1;
  }


  // Store program in temporary ram
  unsigned int cmds[4096];
  int num_cmds = fread(cmds, sizeof(unsigned char), 4096, ptr);
  fclose(ptr);

  // write program to ROM.
  for (int i = 0; i < num_cmds; i++) {
      write_next(&addr, cmds[i]);
  }
  addr = 0;

  // run main program (setting r30 to 36000 is a hack to exit. TODO: make it better :))
  while (read_reg(30) != 36000) {
      run_cmd(&addr);
  }

  // print out registers at end if needed.
  if (argc > 2 && strcmp(argv[2], "-r") == 0) {
    printf("Registers: \n");
    for (int i = 0; i < 32; i++) {
      printf("reg%d: %u\n", i, read_reg(i));
    }
    printf("\n)");
  }

  return 0;
}

