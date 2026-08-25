
#include "chip8.h"
#include <stdbool.h>
#define MAX_BREAKPOINTS 16

typedef struct {
    uint16_t breakpoints[MAX_BREAKPOINTS];
    int num_breakpoints;
    bool step_mode;
} Debugger;

void debugger_init(Debugger *dbg);
void debugger_print_state(Chip8 *chip8);
bool debugger_has_breakpoint(Debugger *dbg, uint16_t addr);
void debugger_add_breakpoint(Debugger *dbg, uint16_t addr);
void debugger_remove_breakpoint(Debugger *dbg, uint16_t addr);
void debugger_repl(Debugger *dbg, Chip8 *chip8);
