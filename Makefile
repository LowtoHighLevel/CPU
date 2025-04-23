CC=zig cc
CFLAGS=-Iinclude

SRCS=src/main.c \
     src/alu.c \
     src/regs.c \
     src/cpu.c \
     src/memory.c \



.PHONY: all clean main target

all: clean main

main: target target/main

target:
	@mkdir -p target

target/main: $(SRCS)
	@$(CC) $(CFLAGS) -o $@ $(SRCS)
	@echo "Compiled: $@ from $(SRCS)"
clean:
	@rm -rf target
	@echo "Cleaned all files!"
