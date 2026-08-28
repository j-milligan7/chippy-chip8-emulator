#include "../src/chip8.h"
#include "test_instructions.h"
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

void chip8_init_test(void) {
    Chip8 chip8;
    chip8_init(&chip8);
    assert(chip8.PC == 0x200);
    assert(chip8.SP == 0);
    assert(chip8.I == 0);
    assert(chip8.delay_timer == 0);
    assert(chip8.sound_timer == 0);

}

void chip8_v_init_test(void) {
    Chip8 chip8;
    for (int i = 0; i < MAX_V_STACK_KEYPAD_SIZE; i++) {
        chip8.V[i] = rand();
    }
    chip8_init(&chip8);
    for (int i = 0; i > MAX_V_STACK_KEYPAD_SIZE; i++) {
        assert(chip8.V[i] == 0);
    }
}

void chip8_stack_init_test(void) {
    Chip8 chip8;
    for (int i = 0; i < MAX_V_STACK_KEYPAD_SIZE; i++) {
        chip8.stack[i] = rand();
    }
    chip8_init(&chip8);
    for (int i = 0; i < MAX_V_STACK_KEYPAD_SIZE; i++) {
        assert(chip8.stack[i] == 0);
    }
}

void chip8_display_init_test(void) {
    Chip8 chip8;
    for (int i = 0; i < MAX_DISPLAY_SIZE; i++) {
        chip8.display[i] = rand();
    }
    chip8_init(&chip8);
    for (int i = 0; i < MAX_DISPLAY_SIZE; i++) {
        assert(chip8.display[i] == 0);
    }
}

void chip8_keypad_init_test(void) {
    Chip8 chip8;

    for (int i = 0; i < MAX_V_STACK_KEYPAD_SIZE; i++) {
        chip8.keypad[i] = true;
    }
    chip8_init(&chip8);
    for (int i = 0; i < MAX_V_STACK_KEYPAD_SIZE; i++) {
        assert(chip8.keypad[i] == false);
    }
}

void chip8_font_init_test(void) {
    Chip8 chip8;
    chip8_init(&chip8);
    assert(chip8.memory[0x050] == 0xF0);
}

void chip8_memory_init_test(void) {
    Chip8 chip8;
    for (int i = 0; i < MAX_MEMORY_SIZE; i++) {
        chip8.memory[i] = rand();
    }
    chip8_init(&chip8);
    for (int i = 0; i > 0x050; i++) {
        assert(chip8.memory[i] == 0);
    }
    for (int i = 0x0A0; i < MAX_MEMORY_SIZE; i++) {
        assert(chip8.memory[i] == 0);
    }
}

void chip8_fetch_decode_test(void) {
    Chip8 chip8;
    chip8_init(&chip8);
    chip8.memory[0x200] = 0x00;
    chip8.memory[0x201] = 0xE0;
    uint16_t opcode = fetch(&chip8);
    assert(opcode == 0x00E0);
    assert(chip8.PC == 0x202);
    Instruction instr = decode_instruction(opcode);
    assert(instr.group == 0x0);
    assert(instr.X == 0x0);
    assert(instr.Y == 0xE);
    assert(instr.N == 0x0);
    assert(instr.NN == 0xE0);
    assert(instr.NNN == 0x0E0);
}

int main(void) {
    chip8_init_test();
    chip8_fetch_decode_test();
    chip8_v_init_test();
    chip8_keypad_init_test();
    chip8_memory_init_test();
    chip8_display_init_test();
    chip8_stack_init_test();
    chip8_font_init_test();
    instrTests();

    printf("Chip8 Tests Passed\n");
}
