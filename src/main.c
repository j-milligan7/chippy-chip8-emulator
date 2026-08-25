#include "chip8.h"
#include "display.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "debug.h"
int main(int argc, char **argv){
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage is %s <rom_path> [--debug]\n", argv[0]);
        return 1;
    }
    bool start_in_debug = (argc == 3 && strcmp(argv[2], "--debug") == 0);
    srand(time(NULL));
    Chip8 chip8;
    chip8_init(&chip8);

    if (!chip8_load_rom(&chip8, argv[1])) {
        return 1;
    }

    if (!display_init()) {
        return 1;
    }

    Debugger dbg;
    debugger_init(&dbg);
    dbg.step_mode = start_in_debug;
    display_set_color(199, 125, 255);
    display_back_color(18, 0, 31);
    chip8_loop(&chip8, &dbg);
    display_cleanup();
    return 0;
}
