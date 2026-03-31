#include <dev/rom.h>

#ifdef DEV_ROM
#include <bus.h>
#include <stdio.h>
#include <util.h>

unsigned char rom[ROM_SIZE];

BUS_DEV rom_device;
int rom_dev_idx;

void write_rom_dummy(size_t offset, uint8_t val) {
    return;
}

uint8_t read_rom_char(size_t offset) {
    if (offset >= 0 && offset < ROM_SIZE) {
        return rom[offset];
    }
    return 0;
}

void rom_init() {
    rom_device.address = ROM_ADDR;
    rom_device.length = ROM_SIZE;
    rom_device.read_char = read_rom_char;
    rom_device.write_char = write_rom_dummy;
    rom_dev_idx = register_bus_device(&rom_device);
}

union int_to_char {
  data_t ic_val;
  uint8_t ic_char[sizeof(data_t)];
};

#endif
void write_rom_char(data_t addr, uint8_t data) {
    #ifdef DEV_ROM
    rom[addr] = data;
    #endif
}

void write_rom(data_t addr, instr_t data) {
    #ifdef DEV_ROM
        union int_to_char conv;
        conv.ic_val = data;
        for (int i = 0; i < sizeof(instr_t); i++) {
            write_rom_char(addr + i, conv.ic_char[i]);
        }
    #endif
}