#include "instructions.h"
#include "chip8.h"
#include <stdint.h>
#include <stdlib.h>

void op_0NNN(Chip8 *chip8, uint16_t nnn) {
    return;
}

void op_00E0(Chip8 *chip8) {
    //clear screen
}

void op_00EE(Chip8 *chip8) {
    chip8->SP--;
    chip8->PC = chip8->stack[chip8->SP];
}

void op_2NNN(Chip8 *chip8, uint16_t nnn) {
    chip8->stack[chip8->SP] = chip8->PC;
    chip8->SP++;
    chip8->PC = nnn;
}

void op_1NNN(Chip8 *chip8, uint16_t nnn) {
    chip8->PC = nnn;
}

void op_3XNN(Chip8 *chip8, uint8_t x, uint8_t nn) {
    if (chip8->V[x] == nn) {
        chip8->PC += 2;
    }
}

void op_4XNN(Chip8 *chip8, uint8_t x, uint8_t nn) {
    if (chip8->V[x] != nn) {
        chip8->PC += 2;
    }
}

void op_5XY0(Chip8 *chip8, uint8_t x, uint8_t y) {
    if (chip8->V[x] == chip8->V[y]) {
        chip8->PC += 2;
    }
}

void op_9XY0(Chip8 *chip8, uint8_t x, uint8_t y) {
    if (chip8->V[x] != chip8->V[y]) {
        chip8->PC += 2;
    }
}

void op_6XNN(Chip8 *chip8, uint8_t x, uint8_t nn) {
    chip8->V[x] = nn;
}

void op_7XNN(Chip8 *chip8, uint8_t x, uint8_t nn) {
    chip8->V[x] += nn;
}

void op_8XY0(Chip8 *chip8, uint8_t x, uint8_t y) {
    chip8->V[x] = chip8->V[y];
}

void op_8XY1(Chip8 *chip8, uint8_t x, uint8_t y) {
    chip8->V[x] |= chip8->V[y];
}

void op_8XY2(Chip8 *chip8, uint8_t x, uint8_t y) {
    chip8->V[x] &= chip8->V[y];
}

void op_8XY3(Chip8 *chip8, uint8_t x, uint8_t y) {
    chip8->V[x] ^= chip8->V[y];
}

void op_8XY4(Chip8 *chip8, uint8_t x, uint8_t y) {
    uint16_t sum = chip8->V[x] + chip8->V[y];
    chip8->V[0x0F] = sum > 255;
    chip8->V[x] = sum & 0xFF;
}

void op_8XY5(Chip8 *chip8, uint8_t x, uint8_t y) {
    if (chip8->V[x] > chip8->V[y]) {
        chip8->V[0xF] = 1;
    }
    else {
        chip8->V[0xF] = 0;
    }
    chip8->V[x] = chip8->V[x] - chip8->V[y];
}

void op_8XY7(Chip8 *chip8, uint8_t x, uint8_t y) {
    if (chip8->V[y] > chip8->V[x]) {
        chip8->V[0xF] = 1;
    }
    else {
        chip8->V[0xF] = 0;
    }
    chip8->V[x] = chip8->V[y] - chip8->V[x];
}

void op_8XY6(Chip8 *chip8, uint8_t x, uint8_t y) {
    chip8->V[x] = chip8->V[y];
    chip8->V[0xF] = chip8->V[x] & 0x01;
    chip8->V[x] >>= 1;

}

void op_8XYE(Chip8 *chip8, uint8_t x, uint8_t y) {
    chip8->V[x] = chip8->V[y];
    chip8->V[0xF] = (chip8->V[x] & 0x80) >> 7;
    chip8->V[x] <<= 1;
}

void op_ANNN(Chip8 *chip8, uint16_t nnn) {
    chip8->I = nnn;
}

void op_BNNN(Chip8 *chip8, uint16_t nnn) {
    chip8->PC = nnn + chip8->V[0];
}

void op_CXNN(Chip8 *chip8, uint8_t x ,uint8_t nn) {
    uint8_t random = rand();
    chip8->V[x] = (nn & (uint8_t)random);
}

void op_DXYN(Chip8 *chip8, uint8_t x, uint8_t y, uint8_t n) {
    //need to do display :(
}
