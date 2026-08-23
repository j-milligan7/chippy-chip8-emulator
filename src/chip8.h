#include <stdint.h>
#include "instructions.h"
typedef struct {
    uint8_t memory[4096]; //RAM
    uint8_t V[16]; // array of all general purpose registers [V0 -> VF]
    uint16_t I; // INDEX REGISTER
    uint16_t PC; // PROGRAM COUNTER
    uint16_t stack[16];
    uint8_t SP; // STACK POINTER
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t display[64 * 32]; //DISPLAY
    bool keypad[16];
} Chip8;

void chip8_init(Chip8 *chip8);

void chip8_loop(Chip8 *chip8);

uint16_t fetch(Chip8 *chip8);

Instruction decode_instruction(uint16_t opcode);

void execute_instruction(Chip8 *chip8, Instruction instr);
