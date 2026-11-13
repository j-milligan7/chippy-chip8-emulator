#include "test_instructions.h"
#include "..//src/chip8.h"
#include "..//src/instructions.h"
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
  for (int i = 0; i < MAX_DISPLAY_SIZE; i *= 3) {
    chip8.display[i] ^= 1;
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
  assert(chip8.stack[0] == 0x200);
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
  assert(chip8.V[0] == 250);
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
  chip8_init(&chip8);
  chip8.V[0] = 0;
  op_8XY6(&chip8, 0);
  assert(chip8.V[0xF] == 0);
  assert(chip8.V[0] == 0);
  chip8.V[1] = 255;
  op_8XY6(&chip8, 1);
  assert(chip8.V[0xF] == 1);
  assert(chip8.V[1] == 127);
}

void op_8XYE_tests(void) {
  Chip8 chip8;
  chip8_init(&chip8);
  chip8.V[0] = 0x80;
  op_8XYE(&chip8, 0);
  assert(chip8.V[0] == 0x00);
  assert(chip8.V[0xF] == 1);
  chip8.V[1] = 0x40;
  op_8XYE(&chip8, 1);
  assert(chip8.V[1] == 0x80);
  assert(chip8.V[0xF] == 0);
}

void op_ANNN_tests(void) {
  Chip8 chip8;
  chip8_init(&chip8);
  chip8.I = 0;
  op_ANNN(&chip8, 0x345);
  assert(chip8.I == 0x345);
}

void op_BXNN_tests(void) {
  Chip8 chip8;
  chip8_init(&chip8);
  chip8.V[0] = 5;
  op_BXNN(&chip8, 0x200, 0);
  assert(chip8.PC == 0x205);
}

void op_CXNN_tests(void) {
  Chip8 chip8;
  chip8_init(&chip8);
  op_CXNN(&chip8, 0, 0x0F);
  assert((chip8.V[0] & 0xF0) == 0);
}

void op_DXYN_tests(void) {
  Chip8 chip8;
  chip8_init(&chip8);
  chip8.I = 0x300;
  chip8.memory[0x300] = 0x80;
  chip8.V[0] = 0;
  chip8.V[1] = 0;
  op_DXYN(&chip8, 0, 1, 1);
  assert(chip8.display[0] == 1);
  assert(chip8.V[0xF] == 0);
}

void op_EX9E_tests(void) {
  Chip8 chip8;
  chip8_init(&chip8);
  chip8.V[0] = 5;
  chip8.keypad[5] = 1;
  chip8.PC = 0x200;

  op_EX9E(&chip8, 0);
  assert(chip8.PC == 0x202);
}

void op_EXA1_tests(void) {
  Chip8 chip8;
  chip8_init(&chip8);
  chip8.V[0] = 5;
  chip8.keypad[5] = 0;
  chip8.PC = 0x200;
  op_EXA1(&chip8, 0);
  assert(chip8.PC == 0x202);
}

void op_FX07_tests(void) {
  Chip8 chip8;
  chip8_init(&chip8);
  chip8.delay_timer = 30;
  op_FX07(&chip8, 0);
  assert(chip8.V[0] == 30);
}

void op_FX15_tests(void) {
  Chip8 chip8;
  chip8_init(&chip8);
  chip8.V[0] = 30;
  op_FX15(&chip8, 0);
  assert(chip8.delay_timer == 30);
}

void op_FX18_tests(void) {
  Chip8 chip8;
  chip8_init(&chip8);
  chip8.V[0] = 60;
  op_FX18(&chip8, 0);
  assert(chip8.sound_timer == 60);
}

void op_FX1E_tests(void) {
  Chip8 chip8;
  chip8_init(&chip8);
  chip8.I = 0;
  chip8.V[0] = 10;
  op_FX1E(&chip8, 0);
  assert(chip8.I == 10);
}

void op_FX0A_tests(void) {
  Chip8 chip8;
  chip8_init(&chip8);
  chip8.PC = 0x200;
  for (int i = 0; i < 16; i++) {
    chip8.keypad[i] = 0;
  }
  op_FX0A(&chip8, 0);
  assert(chip8.PC == 0x1FE);
  chip8.keypad[1] = 1;
  op_FX0A(&chip8, 0);
  assert(chip8.V[0] == 1);
}

void op_FX29_tests(void) {
  Chip8 chip8;
  chip8_init(&chip8);
  chip8.V[0] = 0xA;
  op_FX29(&chip8, 0);
  assert(chip8.I == 0x82);
}

void op_FX33_tests(void) {
  Chip8 chip8;
  chip8_init(&chip8);
  chip8.V[0] = 123;
  chip8.I = 0;
  op_FX33(&chip8, 0);
  assert(chip8.memory[chip8.I] == 1);
  assert(chip8.memory[chip8.I + 1] == 2);
  assert(chip8.memory[chip8.I + 2] == 3);
}

void op_FX55_tests(void) {
  Chip8 chip8;
  chip8_init(&chip8);
  chip8.V[0] = 10;
  chip8.V[1] = 20;
  chip8.I = 0x300;
  op_FX55(&chip8, 1);
  assert(chip8.memory[0x300] == 10);
  assert(chip8.memory[0x301] == 20);
}
void op_FX65_tests(void) {
  Chip8 chip8;
  chip8_init(&chip8);

  chip8.I = 0x300;
  chip8.memory[0x300] = 10;
  chip8.memory[0x301] = 20;
  chip8.memory[0x302] = 30;

  op_FX65(&chip8, 2);

  assert(chip8.V[0] == 10);
  assert(chip8.V[1] == 20);
  assert(chip8.V[2] == 30);
  assert(chip8.I == 0x303);
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
  op_8XYE_tests();
  op_ANNN_tests();
  op_BXNN_tests();
  op_CXNN_tests();
  op_DXYN_tests();
  op_EX9E_tests();
  op_EXA1_tests();
  op_FX07_tests();
  op_FX15_tests();
  op_FX18_tests();
  op_FX1E_tests();
  op_FX0A_tests();
  op_FX29_tests();
  op_FX33_tests();
  op_FX55_tests();
  op_FX65_tests();
  printf("Instruction Tests Passed\n");
}
