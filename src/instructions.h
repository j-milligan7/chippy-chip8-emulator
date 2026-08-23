
#ifndef INSTRUCTIONS_H
#define  INSTRUCTIONS_H
#include <stdint.h>

typedef struct Chip8 Chip8;


typedef struct {
    uint8_t group;
    uint8_t X;
    uint8_t Y;
    uint8_t N;
    uint8_t NN;
    uint16_t NNN;
} Instruction;


#include <stdint.h>

typedef struct Chip8 Chip8;

/* 0x0 instructions */
void op_0NNN(Chip8 *chip8, uint16_t nnn);
void op_00E0(Chip8 *chip8);
void op_00EE(Chip8 *chip8);

/* 0x1 - 0x7 instructions */
void op_1NNN(Chip8 *chip8, uint16_t nnn);
void op_2NNN(Chip8 *chip8, uint16_t nnn);
void op_3XNN(Chip8 *chip8, uint8_t x, uint8_t nn);
void op_4XNN(Chip8 *chip8, uint8_t x, uint8_t nn);
void op_5XY0(Chip8 *chip8, uint8_t x, uint8_t y);
void op_6XNN(Chip8 *chip8, uint8_t x, uint8_t nn);
void op_7XNN(Chip8 *chip8, uint8_t x, uint8_t nn);

/* 0x8 instructions */
void op_8XY0(Chip8 *chip8, uint8_t x, uint8_t y);
void op_8XY1(Chip8 *chip8, uint8_t x, uint8_t y);
void op_8XY2(Chip8 *chip8, uint8_t x, uint8_t y);
void op_8XY3(Chip8 *chip8, uint8_t x, uint8_t y);
void op_8XY4(Chip8 *chip8, uint8_t x, uint8_t y);
void op_8XY5(Chip8 *chip8, uint8_t x, uint8_t y);
void op_8XY6(Chip8 *chip8, uint8_t x, uint8_t y);
void op_8XY7(Chip8 *chip8, uint8_t x, uint8_t y);
void op_8XYE(Chip8 *chip8, uint8_t x, uint8_t y);

/* 0x9 - 0xD instructions */
void op_9XY0(Chip8 *chip8, uint8_t x, uint8_t y);
void op_ANNN(Chip8 *chip8, uint16_t nnn);
void op_BNNN(Chip8 *chip8, uint16_t nnn);
void op_CXNN(Chip8 *chip8, uint8_t x, uint8_t nn);
void op_DXYN(Chip8 *chip8, uint8_t x, uint8_t y, uint8_t n);

/* 0xE instructions */
void op_EX9E(Chip8 *chip8, uint8_t x);
void op_EXA1(Chip8 *chip8, uint8_t x);

/* 0xF instructions */
void op_FX07(Chip8 *chip8, uint8_t x);
void op_FX0A(Chip8 *chip8, uint8_t x);
void op_FX15(Chip8 *chip8, uint8_t x);
void op_FX18(Chip8 *chip8, uint8_t x);
void op_FX1E(Chip8 *chip8, uint8_t x);
void op_FX29(Chip8 *chip8, uint8_t x);
void op_FX33(Chip8 *chip8, uint8_t x);
void op_FX55(Chip8 *chip8, uint8_t x);
void op_FX65(Chip8 *chip8, uint8_t x);




#endif
