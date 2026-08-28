#include "..//src/chip8.h"
#include "..//src/instructions.h"
#include <assert.h>
#include <stdint.h>

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
    chip8.V[0] = 0x20;
    uint8_t nn = 0x20;
    op_3XNN(&chip8, 0, nn);
    assert(chip8.PC == 0x204);
    chip8.PC = 0x200;
    op_3XNN(&chip8, 1, nn);
    assert(chip8.PC == 0x202);
}
