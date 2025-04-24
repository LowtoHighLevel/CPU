CC=zig cc
CFLAGS=-Iinclude

OUTPUT=main
ifeq ($(OS),Windows_NT)
    OUTPUT = target/emu.exe
endif


SRCS=src/main.c \
     src/alu.c \
     src/regs.c \
     src/cpu.c \
     src/memory.c \



.PHONY: all clean main target

all: clean $(OUTPUT)


target/emu.exe: main
	@cp target/emu target/emu.exe
	@echo "Created exe file"

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
