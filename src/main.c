#include <stdio.h>
#include <cpu.h>
#include <regs.h>
#include <mem.h>


void print_binary(unsigned int val) {
  for (int i = 31; i >= 0; i--) {
    printf("%u", (val >> i) & 0b1);
  }
}



void write_next(unsigned int * addr, unsigned int val) {
  write_rom(*addr, val);
  *addr += 4;
}


int main(int argc, char * argv[]) {
  unsigned char carry = 0, zero = 0, overflow = 0, neg = 0;
  unsigned int addr = 0;

   FILE* ptr = fopen(argv[1],"rb");

  if (ptr == NULL) {
    printf("No such file.\n");
    return 1;
  }


  unsigned int cmds[4096];

  int num_cmds = fread(cmds, sizeof(unsigned char), 4096, ptr);
  fclose(ptr);

  for (int i = 0; i < num_cmds; i++) {
      write_next(&addr, cmds[i]);
  }
  

  addr = 0;
  
  for (int i = 0; i < num_cmds; i++) {
    run_cmd(&addr, &carry, &zero, &overflow, &neg);
  }
  
  printf("Registers: \n");
  for (int i = 0; i < 32; i++) {
    printf("reg%d: %u\n", i, read_reg(i));
  }
  printf("\n)");

  return 0;
}

