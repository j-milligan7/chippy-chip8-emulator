#include "..//src/chip8.h"
#include "..//src/instructions.h"
#include "test_instructions.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

void op_00E0_tests(void) {
    Chip8 chip8;
    chip8_init(&chip8);
    // test blank display
    op_00E0(&chip8);
    for (int i = 0; i < MAX_DISPLAY_SIZE; i++) {
        assert(chip8.display[i] == 0);
    }
    for (int i = 0; i < MAX_DISPLAY_SIZE; i++) {
        chip8.display[i] ^= 1;
    }
    // test full display
    op_00E0(&chip8);
    for (int i = 0; i < MAX_DISPLAY_SIZE; i++) {
        assert(chip8.display[i] == 0);
    }
    for (int i = 0; i < MAX_DISPLAY_SIZE; i*=3) {
        chip8.display[i] ^=1;
    }
    // test partial display
    op_00E0(&chip8);
    for (int i = 0; i < MAX_DISPLAY_SIZE; i++) {
        assert(chip8.display[i] == 0);
    }
}

void op_00EE_tests(void) {
    Chip8 chip8;
    chip8_init(&chip8);
    chip8.SP = 1;
    chip8.stack[0] = 0x204;
    op_00EE(&chip8);
    assert(chip8.SP == 0);
    assert(chip8.PC == 0x204);
}

void op_2NNN_tests(void) {
    Chip8 chip8;
    chip8_init(&chip8);
    uint16_t nnn = 0x210;
    op_2NNN(&chip8, nnn);
    assert(chip8.stack[0] = 0x200);
    assert(chip8.SP == 1);
    assert(chip8.PC == nnn);

    chip8.PC = 0x200;
    chip8.SP = 16;
    op_2NNN(&chip8, nnn);
    assert(chip8.SP == 16);
    assert(chip8.PC == 0x200);
}

void op_1NNN_tests(void) {
    Chip8 chip8;
    chip8_init(&chip8);
    uint16_t nnn = 0x300;
    op_1NNN(&chip8, nnn);
    assert(chip8.PC == nnn);
}

void op_3XNN_tests(void) {
    Chip8 chip8;
    chip8_init(&chip8);
    chip8.V[0] = 20;
    uint8_t nn = 20;
    op_3XNN(&chip8, 0, nn);
    assert(chip8.PC == 0x202);
    chip8.PC = 0x200;
    chip8.V[1] = 0x40;
    op_3XNN(&chip8, 1, nn);
    assert(chip8.PC == 0x200);
}

void op_4XNN_tests(void) {
    Chip8 chip8;
    chip8_init(&chip8);
    chip8.V[0] = 0x20;
    uint8_t nn = 0x20;
    op_4XNN(&chip8, 0, nn);
    assert(chip8.PC == 0x200);
    chip8.PC = 0x200;
    chip8.V[1] = 0x30;
    op_4XNN(&chip8, 1, nn);
    assert(chip8.PC == 0x202);
}

void op_5XY0_tests(void) {
    Chip8 chip8;
    chip8_init(&chip8);
    chip8.V[0] = 0x30;
    chip8.V[1] = 0x30;
    op_5XY0(&chip8, 0, 1);
    assert(chip8.PC == 0x202);
    chip8.PC = 0x200;
    chip8.V[1] = 0x40;
    assert(chip8.PC == 0x200);
}

void op_6XNN_tests(void) {
    Chip8 chip8;
    chip8_init(&chip8);
    op_6XNN(&chip8, 0, 0);
    assert(chip8.V[0] == 0);
    op_6XNN(&chip8, 1, 255);
    assert(chip8.V[1] == 255);
    for (int i = 2; i < MAX_V_STACK_KEYPAD_SIZE; i++) {
        assert(chip8.V[i] == 0);
    }
}

void op_7XNN_tests(void) {
    Chip8 chip8;
    chip8_init(&chip8);
    op_7XNN(&chip8, 0, 50);
    assert(chip8.V[0] == 50);
    op_7XNN(&chip8, 0, 200);
    assert(chip8.V[0] == 250 );
}

void op_8XY0_tests(void) {
    Chip8 chip8;
    chip8_init(&chip8);
    chip8.V[1] = 10;
    op_8XY0(&chip8, 0, 1);
    assert(chip8.V[0] == 10);
    assert(chip8.V[0xF] == 0);
}

void op_8XY1_tests(void) {
    Chip8 chip8;
    chip8_init(&chip8);
    chip8.V[1] = 0x0F;
    chip8.V[0] = 0xF0;
    op_8XY1(&chip8, 0, 1);
    assert(chip8.V[0] == 0xFF);
    chip8.V[1] = 0;
    chip8.V[0] = 0;
    op_8XY1(&chip8, 0, 1);
    assert(chip8.V[0] == 0);
    chip8.V[1] = 1;
    chip8.V[0] = 1;
    op_8XY1(&chip8, 0, 1);
    assert(chip8.V[0] == 1);
    assert(chip8.V[0xF] == 0);
}

void op_8XY2_tests(void) {
    Chip8 chip8;
    chip8_init(&chip8);
    chip8.V[1] = 0x0F;
    chip8.V[0] = 0xFF;
    op_8XY2(&chip8, 0, 1);
    assert(chip8.V[0] == 0x0F);
    chip8.V[1] = 0;
    chip8.V[0] = 0;
    op_8XY2(&chip8, 0, 1);
    assert(chip8.V[0] == 0);
    chip8.V[1] = 1;
    chip8.V[0] = 1;
    op_8XY2(&chip8, 0, 1);
    assert(chip8.V[0] == 1);
    assert(chip8.V[0xF] == 0);
}

void op_8XY3_tests(void) {
    Chip8 chip8;
    chip8_init(&chip8);
    chip8.V[1] = 0x0F;
    chip8.V[0] = 0xFF;
    op_8XY3(&chip8, 0, 1);
    assert(chip8.V[0] == 0xF0);
    chip8.V[1] = 0;
    chip8.V[0] = 0;
    op_8XY3(&chip8, 0, 1);
    assert(chip8.V[0] == 0);
    chip8.V[1] = 1;
    op_8XY3(&chip8, 0, 1);
    assert(chip8.V[0] == 1);
}

void op_8XY4_tests(void) {
    Chip8 chip8;
    chip8_init(&chip8);
    chip8.V[0] = 200;
    chip8.V[1] = 55;
    op_8XY4(&chip8, 0, 1);
    assert(chip8.V[0] == 255);
    assert(chip8.V[0xF] == 0);
    chip8.V[2] = 1;
    op_8XY4(&chip8, 0, 2);
    assert(chip8.V[0] == 0);
    assert(chip8.V[0xF] == 1);
}

void op_8XY5_tests(void) {
    Chip8 chip8;
    chip8_init(&chip8);
    chip8.V[0] = 50;
    chip8.V[1] = 40;
    chip8.V[2] = 20;
    op_8XY5(&chip8, 0, 1);
    assert(chip8.V[0] == 10);
    assert(chip8.V[0xF] == 1);
    op_8XY5(&chip8, 0, 2);
    assert(chip8.V[0] == 246);
    assert(chip8.V[0xF] == 0);
}

void op_8XY6_tests(void) {
    Chip8 chip8;
    // finish later...
}

void instrTests(void) {
    op_1NNN_tests();
    op_2NNN_tests();
    op_3XNN_tests();
    op_4XNN_tests();
    op_5XY0_tests();
    op_6XNN_tests();
    op_7XNN_tests();
    op_8XY0_tests();
    op_8XY1_tests();
    op_8XY2_tests();
    op_8XY3_tests();
    op_8XY4_tests();
    op_8XY5_tests();
    op_8XY6_tests();

    printf("Instruction Tests Passed\n");
}
