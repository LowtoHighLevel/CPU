CC=zig cc
CFLAGS=-Iinclude

SRCS=src/main.c \
     src/alu.c \
     src/regs.c \
     src/cpu.c \
     src/memory.c \



.PHONY: all clean main target

all: clean main target/gen

main: target target/emu

target:
	@mkdir -p target

target/emu: $(SRCS)
	@$(CC) $(CFLAGS) -o $@ $(SRCS)
	@echo "Compiled: $@ from $(SRCS)"
clean:
	@rm -rf target
	@rm -f out.bin
	@echo "Cleaned all files!"

target/gen: gen.c
	@$(CC) -o $@ $<
