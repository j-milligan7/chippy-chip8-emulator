#include "instructions.h"
#include "chip8.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void op_00E0(Chip8 *chip8) {
    memset(chip8->display, 0, sizeof(chip8->display));
}

void op_00EE(Chip8 *chip8) {
    chip8->SP--;
    chip8->PC = chip8->stack[chip8->SP];
}

void op_2NNN(Chip8 *chip8, uint16_t nnn) {
    if (chip8->SP >= 16) {
        return;
    }
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
    chip8->V[0xF] = 0;
}

void op_8XY2(Chip8 *chip8, uint8_t x, uint8_t y) {
    chip8->V[x] &= chip8->V[y];
    chip8->V[0xF] = 0;
}

void op_8XY3(Chip8 *chip8, uint8_t x, uint8_t y) {
    chip8->V[x] ^= chip8->V[y];
    chip8->V[0xF] = 0;
}

void op_8XY4(Chip8 *chip8, uint8_t x, uint8_t y) {
    uint16_t sum = chip8->V[x] + chip8->V[y];
    uint8_t flag = sum > 255;
    chip8->V[x] = sum & 0xFF;
    chip8->V[0xF] = flag;
}

void op_8XY5(Chip8 *chip8, uint8_t x, uint8_t y) {
    uint8_t flag = (chip8->V[x] >= chip8->V[y]);
    chip8->V[x] = chip8->V[x] - chip8->V[y];
    chip8->V[0xF] = flag;
}

void op_8XY7(Chip8 *chip8, uint8_t x, uint8_t y) {
    uint8_t flag = (chip8->V[y] >= chip8->V[x]);
    chip8->V[x] = chip8->V[y] - chip8->V[x];
    chip8->V[0xF] = flag;
}

void op_8XY6(Chip8 *chip8, uint8_t x) {
    chip8->V[0xF] = chip8->V[x] & 0x1;
    chip8->V[x] >>= 1;

}

void op_8XYE(Chip8 *chip8, uint8_t x) {
    chip8->V[0xF] = (chip8->V[x] & 0x80) >> 7;
    chip8->V[x] <<= 1;
}

void op_ANNN(Chip8 *chip8, uint16_t nnn) {
    chip8->I = nnn;
}

void op_BXNN(Chip8 *chip8, uint16_t nnn, uint8_t x) {
    chip8->PC = nnn + chip8->V[x];
}

void op_CXNN(Chip8 *chip8, uint8_t x ,uint8_t nn) {
    uint8_t random = rand();
    chip8->V[x] = (nn & (uint8_t)random);
}

void op_DXYN(Chip8 *chip8, uint8_t x, uint8_t y, uint8_t n) {
    uint8_t x_coord = chip8->V[x] & 63;
    uint8_t y_coord = chip8->V[y] & 31;
    chip8->V[0xF] = 0;
    for (int i = 0; i < n; i++) {
        uint8_t sprite_byte = chip8->memory[chip8->I + i];
        for (int j = 0; j < 8; j++) {
            if (!(sprite_byte & (0x80 >> j))) {
                continue;
            }
            uint8_t pixel_x = (x_coord + j) % 64;
            uint8_t pixel_y = (y_coord + i) % 32;

            uint16_t index = pixel_y * 64 + pixel_x;
            if (chip8->display[index]) {
                chip8->V[0xF] = 1;
            }
            chip8->display[index] ^= 1;
        }
    }
}

void op_EX9E(Chip8 *chip8, uint8_t x) {
    uint8_t key = chip8->V[x] & 0x0F;
    if (chip8->keypad[key]) {
       chip8->PC += 2;
    }
}

void op_EXA1(Chip8 *chip8, uint8_t x) {
    uint8_t key = chip8->V[x] & 0x0F;
    if (!chip8->keypad[key]) {
        chip8->PC += 2;
    }
}

void op_FX07(Chip8 *chip8, uint8_t x) {
    chip8->V[x] = chip8->delay_timer;
}

void op_FX15(Chip8 *chip8, uint8_t x) {
    chip8->delay_timer = chip8->V[x];
}

void op_FX18(Chip8 *chip8, uint8_t x) {
    chip8->sound_timer = chip8->V[x];
}

void op_FX1E(Chip8 *chip8, uint8_t x) {
    chip8->I += chip8->V[x];
}

void op_FX0A(Chip8 *chip8, uint8_t x) {
    bool key_pressed = false;
    for (int i = 0; i < 16; i++) {
        if (chip8->keypad[i]) {
            chip8->V[x] = i;
            key_pressed = true;
            break;
        }
    }
    if (!key_pressed) {
        chip8->PC -=2;
    }
}

void op_FX29(Chip8 *chip8, uint8_t x) {
    chip8->I = 0x50 + (chip8->V[x] * 5);
}

void op_FX33(Chip8 *chip8, uint8_t x) {
    uint8_t value = chip8->V[x];
    uint8_t arr[3];
    for (int i = 2; i >= 0; i--) {
        arr[i] = value % 10;
        value /= 10;
    }
    for (int i = 0; i < 3; i++) {
        chip8->memory[chip8->I + i] = arr[i];
    }
}

void op_FX55(Chip8 *chip8, uint8_t x) {
    for (int i = 0; i <= x; i++) {
        chip8->memory[chip8->I+i] = chip8->V[i];
    }
    chip8->I += x + 1;
}

void op_FX65(Chip8 *chip8, uint8_t x) {
    for (int i = 0; i <= x; i++) {
        chip8->V[i] = chip8->memory[chip8->I+i];
    }
    chip8->I += x + 1;
}
