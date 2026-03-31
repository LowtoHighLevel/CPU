#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct config_t {
    bool dev_rom;
    bool dev_ram;
    bool dev_char;
    char dev_char_addr[256];
    char dev_rom_addr[256];
    char dev_rom_size[256];
    char dev_ram_size[256];
    char dev_ram_addr[256];
    char cputype[256];
};

void default_config(struct config_t* config) {
    config->dev_char = true;
    config->dev_ram = true;
    config->dev_rom = true;
    strcpy(config->dev_char_addr, "(1024*16)");
    strcpy(config->dev_rom_addr, "0");
    strcpy(config->dev_rom_size, "(1024*7)");
    strcpy(config->dev_ram_addr, "(1024*7)");
    strcpy(config->dev_ram_size, "(1024*8)");
    strcpy(config->cputype, "32");

}

void export_config(struct config_t* config, FILE* fptr) {
    fprintf(fptr, "COPTS= \\\n");
    fprintf(fptr, "    -DCPUTYP=\"%s\" \\\n", config->cputype);
    fprintf(fptr, "    -DDEV \\\n");
    if (config->dev_char) {
        fprintf(fptr, "    -DDEV_CHAR \\\n");
        fprintf(fptr, "    -DDEV_CHAR_ADDR=\"%s\" \\\n", config->dev_char_addr);
    }
    if (config->dev_rom) {
        fprintf(fptr, "    -DDEV_ROM \\\n");
        fprintf(fptr, "    -DROM_SIZE=\"%s\" \\\n", config->dev_rom_size);
        fprintf(fptr, "    -DROM_ADDR=\"%s\" \\\n", config->dev_rom_addr);
    }
    
    if (config->dev_ram) {
        fprintf(fptr, "    -DDEV_RAM \\\n");
        fprintf(fptr, "    -DRAM_SIZE=\"%s\" \\\n", config->dev_ram_size);
        fprintf(fptr, "    -DRAM_ADDR=\"%s\" \\\n", config->dev_ram_addr);
    }
}

int parse_args(struct config_t* config, int argc, char ** argv) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-dev_char") == 0) {
            i++;
            if (strcmp(argv[i], "true") == 0) {
                config->dev_char = true;
            } else config->dev_char = false;
        } else if (strcmp(argv[i], "-dev_char_addr") == 0) {
            i++;
            strcpy(config->dev_char_addr, argv[i]);
        } else if (strcmp(argv[i], "-dev_rom") == 0) {
            i++;
            if (strcmp(argv[i], "true") == 0) {
                config->dev_rom = true;
            } else config->dev_rom = false;
        } else if (strcmp(argv[i], "-dev_rom_addr") == 0) {
            i++;
            strcpy(config->dev_rom_addr, argv[i]);
        } else if (strcmp(argv[i], "-dev_rom_size") == 0) {
            i++;
            strcpy(config->dev_rom_size, argv[i]);
        } else if (strcmp(argv[i], "-dev_ram") == 0) {
            i++;
            if (strcmp(argv[i], "true") == 0) {
                config->dev_ram = true;
            } else config->dev_ram = false;
        } else if (strcmp(argv[i], "-dev_ram_addr") == 0) {
            i++;
            strcpy(config->dev_ram_addr, argv[i]);
        } else if (strcmp(argv[i], "-dev_ram_size") == 0) {
            i++;
            strcpy(config->dev_ram_size, argv[i]);
        } else if (strcmp(argv[i], "-cputype") == 0) {
            i++;
            strcpy(config->cputype, argv[i]);
        } else if (strcmp(argv[i], "-help") == 0) {
            printf("Usage: ./configure <args>\n");
            printf("Arguments:\n");
            printf("  -dev_char <true/false> // Enable Character Device \n");
            printf("  -dev_char_addr <address> // Character Device MMIO Address \n");
            printf("  -dev_rom <true/false> // Enable ROM Device \n");
            printf("  -dev_rom_addr <address> // ROM Device Address \n");
            printf("  -dev_rom_size <size> // ROM Device Size (in bytes) \n");
            printf("  -dev_ram <true/false> // Enable RAM Device \n");
            printf("  -dev_ram_addr <address> // RAM Device Address \n");
            printf("  -dev_ram_size <size> // RAM Device Size (in bytes) \n");
            printf("  -cputype <type> // CPU Type (only 32 supported right now) \n");
            return 1;
        }
    }
    return 0;
}


int main(int argc, char* argv[]) {
    printf("LTHL CPU v2 Configuration Script\n");
    FILE *fptr;

    struct config_t config;
    default_config(&config);
    int ret = parse_args(&config, argc, argv);
    if (ret > 0) return 0;
    // Open the file in write mode
    fptr = fopen("Makefile", "w");

    fprintf(fptr, "include ./make.mk\n");
    export_config(&config, fptr);
    fclose(fptr);

    return 0;
}