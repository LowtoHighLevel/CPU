#include <dev/dev.h>
#include <dev/ram.h>
#include <dev/rom.h>
#include <bus.h>

uint8_t ram[RAM_SIZE];

BUS_DEV ram_device;

void write_ram(size_t offset, uint8_t data) {
    if (offset >= 0 && offset < RAM_SIZE) {
        ram[offset] = data;
    }

}

uint8_t read_ram(size_t offset) {
    if (offset >= 0 && offset < RAM_SIZE) {
        return ram[offset];
    }
    return 0;
}

void ram_init() {
    ram_device.address = RAM_ADDR;
    ram_device.length = RAM_SIZE;
    ram_device.read_char = read_ram;
    ram_device.write_char = write_ram;
    register_bus_device(&ram_device);
}
