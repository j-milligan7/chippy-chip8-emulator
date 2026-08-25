#include "debug.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void debugger_init(Debugger *dbg) {
    dbg->num_breakpoints = 0;
    dbg->step_mode = false;
}

void debugger_print_state(Chip8 *chip8) {
    printf("\n-- PC: 0x%04X  Opcode: 0x%04X  I: 0x%04X  SP: %d --\n", chip8->PC, (chip8->memory[chip8->PC] << 8) | chip8->memory[chip8->PC + 1], chip8->I, chip8->SP);

    for (int i = 0; i < 16; i++) {
        printf("V%X=%02X", i, chip8->V[i]);
        if (i == 7){
            printf("\n");
        }
    }
    printf("\nDelay: %d Sound: %d\n", chip8->delay_timer, chip8->sound_timer);
    printf("Stack ");
    for (int i = 0; i < chip8->SP; i++) {
        printf("0x%04X ", chip8->stack[i]);
    }
    printf("\n");
}

bool debugger_has_breakpoint(Debugger *dbg, uint16_t addr) {
    for (int i = 0; i < dbg->num_breakpoints; i++) {
        if (dbg->breakpoints[i] == addr) {
            return true;
        }
    }
    return false;
}

void debugger_add_breakpoint(Debugger *dbg, uint16_t addr) {
    if (dbg->num_breakpoints < MAX_BREAKPOINTS) {
        dbg->breakpoints[dbg->num_breakpoints++] = addr;
        return;
    }
    fprintf(stderr, "ERROR: ADD BREAKPOINT FAILED\n");
}

void debugger_remove_breakpoint(Debugger *dbg, uint16_t addr) {

    for (int i = 0; i < dbg->num_breakpoints; i++) {
        if (dbg->breakpoints[i] == addr) {
            memmove(&dbg->breakpoints[i], &dbg->breakpoints[i+1], sizeof(dbg->breakpoints[0]) * (dbg->num_breakpoints - i - 1));
            dbg->num_breakpoints--;
            return;
        }
    }
    printf("Address Not found\n");
}

void debugger_repl(Debugger *dbg, Chip8 *chip8) {
    char line[64];
    unsigned int addr;
    for (;;) {
        printf("(dbg) ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            exit(0);
        }

        if (line[0] == 's' || line[0] == '\n') {
            dbg->step_mode = true;
            return;
        }
        else if (line[0] == 'c') {
            dbg->step_mode = false;
            return;
        }
        else if(line[0] == 'b') {
            sscanf(line, "b %x", &addr);
            debugger_add_breakpoint(dbg, addr);
        }
        else if (line[0] == 'd') {
            sscanf(line, "d %x", &addr);
            debugger_remove_breakpoint(dbg, addr);
        }
        else if (line[0] == 'l') {
            for (int i = 0; i < dbg->num_breakpoints-1; i++) {
                printf("0x%4X ", dbg->breakpoints[i]);
            }
            printf("\n");
        }
        else if (line[0] == 'q') {
            exit(0);
        }
        else {
            printf("unrecognised command\n");
        }
    }
}
