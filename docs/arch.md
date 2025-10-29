# Architecture Notes

 1.) 32-bit bus, 32-bit data
 2.) ALU OPS - Add, AND, OR, XOR, ROR, ROL
 
 
## Instruction types
 
### R-Type
```
000 NEGB CARRYIN DDD outreg areg breg
```

### IMM_TYPE
```
001 5-bitreg 24-bitdata
```

### MEMREAD
```
010 00000 IN REG 00000000 STORE REG
```
### MEMWRITE
```
011 00000 ADDR-REG DATA-REG 00000000
```

### JMPREL
```
100 CONDITION 00000000 SHORT-REL
```

### JMPREG
```
101 CONDITION ADDRREG 00000000 00000000
```

## Conditions

0 - Absolute
1 - Zero
2 - Carry
3 - Overflow
4 - Neg
## Registers

r0 - Always zero

r1-30 - General Purpose

r31 - Stack Pointer


