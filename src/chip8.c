#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "chip8.h"

static const uint8_t font_set[] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void chip8_init(Chip8 *chip8) {
    memset(chip8, 0, sizeof(Chip8));
    chip8->PC = 0x200;
    memcpy(&chip8->memory[0x050], font_set, sizeof(font_set));
    //incomplete

}

uint16_t fetch(Chip8 *chip8) {
    uint16_t opcode;
    opcode = ((uint16_t)chip8->memory[chip8->PC] << 8) | (chip8->memory[chip8->PC + 1]);
    chip8->PC += 2;
    return opcode;
}

// use the instruction gotten from fetch
Instruction decode_instruction(uint16_t opcode) {
    Instruction instr;
    instr.group = (opcode &0xF000) >> 12;
    instr.X = (opcode & 0x0F00) >> 8;
    instr.Y = (opcode & 0x00F0) >> 4;
    instr.N = opcode & 0x000F;
    instr.NN = opcode & 0x00FF;
    instr.NNN = opcode & 0x0FFF;
    return instr;
}

void execute_instruction(Chip8 *chip8, Instruction instr) {
    switch (instr.group) {
        case 0x0 :
            switch(instr.X) {
                //Rest of instructions
            }
            break;
        case 0x1:
            switch (instr.X) {

            }
            break;
        case 0x2:
            switch (instr.X) {

            }
            break;
        // etc... will do later
    }
}
