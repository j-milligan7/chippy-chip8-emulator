#include "chip8.h"
#include "display.h"
#include <stdio.h>
int main(int argc, char **argv){
    if (argc > 2) {
        fprintf(stderr, "Usage is %s <rom_path>\n", argv[0]);
        return 1;
    }
    Chip8 chip8;
    chip8_init(&chip8);

    if (!chip8_load_rom(&chip8, argv[1])) {
        return 1;
    }

    if (!display_init()) {
        return 1;
    }

    chip8_loop(&chip8);
    return 0;
}
