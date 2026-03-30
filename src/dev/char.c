#include <dev/char.h>
#include <bus.h>
#include <stdio.h>

BUS_DEV char_device;


char read_val;
uint8_t char_read(size_t offset) {
    scanf("%c", &read_val);
    return read_val;
}

void char_write(size_t offset, uint8_t val) {
    printf("%c", val);
}

void char_init() {
    char_device.address = DEV_CHAR_ADDR;
    char_device.length = 1;
    char_device.read_char = char_read;
    char_device.write_char = char_write;
    register_bus_device(&char_device);
}