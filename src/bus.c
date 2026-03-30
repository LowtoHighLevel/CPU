#include <bus.h>
#include <stdio.h>
#include <defs.h>
#include <stdint.h>
#include <util.h>



BUS_DEV* devices[128];


char log_msg[100];

int register_bus_device(BUS_DEV* dev) {
  size_t idx = 0;
  while (devices[idx] != 0) {
    idx++;
  }
  devices[idx] = dev;
  return idx;
}

int unregister_bus_device(int idx) {
  if ((idx >= 128 && idx < 0) || devices[idx] == 0) return -1;
  devices[idx] = 0;
  return 0;
}

unsigned char scan_val;

union int_to_char {
  data_t ic_val;
  uint8_t ic_char[sizeof(data_t)];
};

union instr_to_char {
  instr_t ic_val;
  uint8_t ic_char[sizeof(instr_t)];
};


void write_mem(data_t addr, data_t val) {

  union int_to_char data;
  data.ic_val = val;

  for (int i = 0; i < sizeof(data_t); i++) {
    write_char_mem(addr + i, data.ic_char[i]);
  }
}

instr_t read_instruction(data_t addr) {
  union instr_to_char data;

  for (int i = 0 ; i < sizeof(instr_t); i++) {
    data.ic_char[i] = read_char_mem(addr + i);
  }
  return data.ic_val;
}

data_t read_mem(data_t addr) {
  union int_to_char data;

  for (int i = 0; i < sizeof(data_t); i++) {
    data.ic_char[i] = read_char_mem(addr + i);
  }
  return data.ic_val;
}

void write_char_mem(data_t addr, uint8_t val) {
  for (size_t i = 0; i < 128; i++) {
    if (devices[i] == 0) continue;

    BUS_DEV* device = devices[i];

    sprintf(log_msg, "Attempting to write %c to: %x. Device info: {address: %x, length: %d}\n", val, addr, device->address, device->length);
    log_message(LOG_DEBUG, log_msg);
    if (addr < (device->address + device->length) && addr >= device->address) {
      sprintf(log_msg, "Writing %c to device\n", val);
      log_message(LOG_DEBUG, log_msg);
      device->write_char(addr - device->address, val);
    }
  }
}   

uint8_t read_char_mem(data_t addr) {
  for (size_t i = 0; i < 128; i++) {
    if (devices[i] == 0) continue;

    BUS_DEV* device = devices[i];

    if (addr < (device->address + device->length) && addr >= device->address) {
      return device->read_char(addr - device->address);
    }
  }
  return 0;
}




