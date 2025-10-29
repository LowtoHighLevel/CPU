#ifndef __CPU_H
#define __CPU_H

#define CPU_OP_TYPE_POS 29
#define CPU_OP_CONTROL_POS 24


enum CPU_TYPE {
    CPU_TYPE_REGISTER = 0b000,
    CPU_TYPE_IMM = 0b001,
    CPU_TYPE_MEM_READ = 0b010,
    CPU_TYPE_MEM_WRITE = 0b011,
    CPU_TYPE_JMP_REL = 0100,
    CPU_TYPE_JMP_REG = 0b101

};

/**
 * Initializes the CPU.
 */

void init();
/**
 * Runs a single CPU instruction at address addr.
 * 
 * addr - address to run instruction at.
 */
void run_cmd();


#endif
