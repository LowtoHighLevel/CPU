#include <dev/dev.h>
#include <util.h>

void init_devices() {

    #ifdef DEV_ROM
    rom_init();
    #endif
    
    #ifdef DEV_RAM
    ram_init();
    #endif

    #ifdef DEV_CHAR
    char_init();
    #endif

    log_message(LOG_DEBUG, "Initalized Devices\n");
}