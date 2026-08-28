#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>
#include <stdbool.h>
#include "instructions.h"
#include "debug.h"

#define MAX_MEMORY_SIZE 4096
#define MAX_V_STACK_KEYPAD_SIZE 16
#define MAX_DISPLAY_SIZE 64*32

typedef struct Chip8 Chip8;

 struct Chip8 {
    uint8_t memory[MAX_MEMORY_SIZE]; //RAM
    uint8_t V[MAX_V_STACK_KEYPAD_SIZE]; // array of all general purpose registers [V0 -> VF]
    uint16_t I; // INDEX REGISTER
    uint16_t PC; // PROGRAM COUNTER
    uint16_t stack[MAX_V_STACK_KEYPAD_SIZE];
    uint8_t SP; // STACK POINTER
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t display[MAX_DISPLAY_SIZE]; //DISPLAY
    bool keypad[MAX_V_STACK_KEYPAD_SIZE];
};

void chip8_init(Chip8 *chip8);

void chip8_loop(Chip8 *chip8, Debugger *dbg);

uint16_t fetch(Chip8 *chip8);

Instruction decode_instruction(uint16_t opcode);

void execute_instruction(Chip8 *chip8, Instruction instr);

int chip8_load_rom(Chip8 *chip8, const char *path);

#endif
