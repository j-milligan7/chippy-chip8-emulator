#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "chip8.h"
#include "instructions.h"

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
            switch(instr.NNN) {
                case 0x0E0 :
                    op_00E0(chip8);
                    break;
            }
            switch (instr.NN) {
                case 0xEE :
                    op_00EE(chip8);
                    break;
            }
            break;
        case 0x1 :
            op_1NNN(chip8, instr.NNN);
            break;
        case 0x2:
            op_2NNN(chip8, instr.NNN);
            break;
        case 0x3:
            op_3XNN(chip8, instr.X, instr.NN);
            break;
        case 0x4:
            op_4XNN(chip8, instr.X, instr.NN);
            break;
        case 0x5:
            op_5XY0(chip8, instr.X, instr.Y);
            break;
        case 0x6:
            op_6XNN(chip8, instr.X, instr.NN);
            break;
        case 0x9:
            op_9XY0(chip8, instr.X, instr.Y);
            break;
        case 0x7:
            op_7XNN(chip8, instr.X, instr.NN);
            break;
        case 0x8:
            switch (instr.N) {
                case 0x0 :
                    op_8XY0(chip8, instr.X, instr.Y);
                    break;
                case 0x1:
                    op_8XY1(chip8, instr.X, instr.Y);
                    break;
                case 0x2:
                    op_8XY2(chip8, instr.X, instr.Y);
                    break;
                case 0x3:
                    op_8XY3(chip8, instr.X, instr.Y);
                    break;
                case 0x4:
                    op_8XY4(chip8, instr.X, instr.Y);
                    break;
                case 0x5:
                    op_8XY5(chip8, instr.X, instr.Y);
                    break;
                case 0x6:
                    op_8XY6(chip8, instr.X, instr.Y);
                    break;
                case 0x7:
                    op_8XY7(chip8, instr.X, instr.Y);
                    break;
                case 0xE:
                    op_8XYE(chip8, instr.X, instr.Y);
                    break;
            }
            break;
        case 0xA:
            op_ANNN(chip8, instr.NNN);
            break;
        case 0xB:
            op_BNNN(chip8, instr.NNN);
            break;
        case 0xC:
            op_CXNN(chip8, instr.X, instr.NN);
            break;
        case 0xD:
            op_DXYN(chip8, instr.X, instr.Y, instr.N);
            break;
        case 0xE:
            switch(instr.NN) {
                case 0x9E:
                    op_EX9E(chip8, instr.X);
                    break;
                case 0xA1:
                    op_EXA1(chip8, instr.X);
                    break;
            }
            break;
        case 0xF:
            switch(instr.NN) {
                case 0x07:
                    op_FX07(chip8, instr.X);
                    break;
                case 0x15:
                    op_FX15(chip8, instr.X);
                    break;
                case 0x18:
                    op_FX18(chip8, instr.X);
                    break;
                case 0x1E:
                    op_FX1E(chip8, instr.X);
                    break;
                case 0x0A:
                    op_FX0A(chip8, instr.X);
                    break;
                case 0x29:
                    op_FX29(chip8, instr.X);
                    break;
                case 0x33:
                    op_FX33(chip8, instr.X);
                    break;
                case 0x55:
                    op_FX55(chip8, instr.X);
                    break;
                case 0x65:
                    op_FX65(chip8, instr.X);
                    break;
            }
            break;
        }

    }
