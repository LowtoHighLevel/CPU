CC=zig cc
CFLAGS=-Iinclude

OUTPUT=main
TARGETTYPE=
ifeq ($(OS),Windows_NT)
    OUTPUT = win
	TARGETTYPE=.exe
endif


SRCS=src/main.c \
     src/alu.c \
     src/regs.c \
     src/cpu.c \
     src/memory.c \
	 src/util.c \



.PHONY: all clean target win test

all: clean $(OUTPUT)

win: target/emu.exe target/alutest.exe

main: target/emu target/alutest

test: clean target/alutest$(TARGEETTYPE)
	@target/alutest$($(TARGEETTYPE))

target/emu.exe: target/emu
	@cp target/emu target/emu.exe
	@echo "Created exe file"

target/alutest.exe: target/alutest
	@cp target/alutest target/alutest.exe
	@echo "created test exe file for alu"

target:
	@mkdir -p target

target/emu: target $(SRCS)
	@$(CC) $(CFLAGS) -o $@ $(SRCS)
	@echo "Compiled: $@ from $(SRCS)"


target/alutest: target src/alu.c src/util.c src/regs.c
	@$(CC) $(CFLAGS) -DTEST_ALU -o $@ src/alu.c src/util.c src/regs.c
	@echo "Created test executable for alu"

clean:
	@rm -rf target
	@rm -f out.bin
	@echo "Cleaned all files!"
