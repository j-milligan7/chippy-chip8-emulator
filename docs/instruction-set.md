# Brief Description of all instructions


## 00E0
The clear screen instruction. This works by setting all pixels to 0.

```C
void op_00E0(Chip8 *chip8) {
    memset(chip8->display, 0, sizeof(chip8->display));
}
```

## 00EE
This is a return instruction, it pops the last memory location in the stack and assigns the program counter to it.

```C
void op_00EE(Chip8 *chip8) {
    chip8->SP--;
    chip8->PC = chip8->stack[chip8->SP];
}
```

## 1NNN
The Jump instruction. This sets the program counter to NNN.

```C
void op_1NNN(Chip8 *chip8, uint16_t nnn) {
    chip8->PC = nnn;
}
```

## 2NNN
This is a call instruction, pushes the program counter to the stack, and sets the program counter to NNN.

```C
void op_2NNN(Chip8 *chip8, uint16_t nnn) {
    chip8->stack[chip8->SP] = chip8->PC;
    chip8->SP++;
    chip8->PC = nnn;
}
```

## 3XNN & 4XNN
When these instructions are called, they check whether register VX == NN, 3XNN skips one instruction if they are equal, 4XNN skips if they are not.

```C
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
```

## 5XY0 & 9XY0
These instructions check whether registers VX == VY, 5XY0 skips if they are equal, 9XY0 skips if they are not.

```C
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
```

## 6XNN
This instructions sets the register VX to the value NN.

```C
void op_6XNN(Chip8 *chip8, uint8_t x, uint8_t nn) {
    chip8->V[x] = nn;
}
```

## 7XNN
This instruction adds the value NN to the register VX.

```C
void op_7XNN(Chip8 *chip8, uint8_t x, uint8_t nn) {
    chip8->V[x] += nn;
}
```

## 8XY0
This sets the register VX to VY.

```C
void op_8XY0(Chip8 *chip8, uint8_t x, uint8_t y) {
    chip8->V[x] = chip8->V[y];
}
```

## 8XY1
This sets the register VX to the bitwise OR of VX and VY.

```C
void op_8XY1(Chip8 *chip8, uint8_t x, uint8_t y) {
    chip8->V[x] |= chip8->V[y];
    chip8->V[0xF] = 0;
}
```

## 8XY2
This sets the register VX the the bitwise AND of VX and VY.

```C
void op_8XY2(Chip8 *chip8, uint8_t x, uint8_t y) {
    chip8->V[x] &= chip8->V[y];
    chip8->V[0xF] = 0;
}
```

## 8XY3
This sets the register VX to the bitwise XOR of VX and VY

```C
void op_8XY3(Chip8 *chip8, uint8_t x, uint8_t y) {
    chip8->V[x] ^= chip8->V[y];
    chip8->V[0xF] = 0;
}
```

## 8XY4
This sets the register VX to VX + VY. This instruction also affects the carry flag in the case of an overflow.

```C
void op_8XY4(Chip8 *chip8, uint8_t x, uint8_t y) {
    uint16_t sum = chip8->V[x] + chip8->V[y];
    uint8_t flag = sum > 255;
    chip8->V[x] = sum & 0xFF;
    chip8->V[0xF] = flag;
}
}
```

## 8XY5 & 8XY7
These instructions subtract one register from another. 8XY5 sets VX to VX-VY, while 8XY7 sets VX to VY-VX. These subtractions also affect the carry flag, but this time in the case of an underflow.

```C
void op_8XY5(Chip8 *chip8, uint8_t x, uint8_t y) {
    uint8_t flag = chip8->V[0xF] = (chip8->V[x] >= chip8->V[y]);
    chip8->V[x] = chip8->V[x] - chip8->V[y];
    chip8->V[0xF] = flag;
}

void op_8XY7(Chip8 *chip8, uint8_t x, uint8_t y) {
    uint8_t flag = chip8->V[0xF] = (chip8->V[y] >= chip8->V[x]);
    chip8->V[x] = chip8->V[y] - chip8->V[x];
    chip8->V[0xF] = flag;
}
```

## 8XY6 & 8XYE
These instructions set the register VX to VY, then shift that value by 1, 8XY6 shifts it to the right, 8XYE shifts to the left. VF then gets set to either 0 or 1 dependinf on which bit got pushed out.

```C
void op_8XY6(Chip8 *chip8, uint8_t x) {
    chip8->V[0xF] = chip8->V[x] & 0x1;
    chip8->V[x] >>= 1;

}

void op_8XYE(Chip8 *chip8, uint8_t x) {
    chip8->V[0xF] = (chip8->V[x] & 0x80) >> 7;
    chip8->V[x] <<= 1;
}
```

## ANNN
This sets the index register to the value NNN.

```C
void op_ANNN(Chip8 *chip8, uint16_t nnn) {
    chip8->I = nnn;
}
```

## BXNN
This jumps the program counter to the address NNN + VX.

```C
void op_BXNN(Chip8 *chip8, uint16_t nnn, uint8_t x) {
    chip8->PC = nnn + chip8->V[x];
}
```

## CXNN
This instruction generates a random number, then ANDs it with the value NN and sets the register VX to that value.

```C
void op_CXNN(Chip8 *chip8, uint8_t x ,uint8_t nn) {
    uint8_t random = rand();
    chip8->V[x] = (nn & (uint8_t)random);
}
```

## DXYN
This is the "draw" instruction, it draws an N pixels tall sprite from the memory location at the index register. at the x coordinate held in VX and the y coordinate held in VY. All of the pixels that are on in the sprite will flip the pixels on the screen that it is drawn to. If any pixels are turned off, the VF register gets set to 1.

```C
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
```

note: this was the hardest function by a mile.

## EX9E & EXA1
These instructions are based on keyboard input, EX9E will skip an instruction if a key is pressed, EXA1 will skip if no key is pressed.

```C
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
```

## FX07, FX15 & FX18
These are the timer instructions. FX07 sets VX to the current value of the delay timer. FX15 does the opposite, it sets the delay timer to the value in VX. FX18 sets the sound timer to the value in VX.

```C
void op_FX07(Chip8 *chip8, uint8_t x) {
    chip8->V[x] = chip8->delay_timer;
}

void op_FX15(Chip8 *chip8, uint8_t x) {
    chip8->delay_timer = chip8->V[x];
}

void op_FX18(Chip8 *chip8, uint8_t x) {
    chip8->sound_timer = chip8->V[x];
}
```

## FX1E
The index register gets the value in VX added onto it.

```C
void op_FX1E(Chip8 *chip8, uint8_t x) {
    chip8->I += chip8->V[x];
}
```

## FX0A
This instruction stops executing instructions until a key has been pressed.

```C
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
```

## FX29
This instruction sets the index register to the address of a hexadecimal character in VX (The font character).

```C
void op_FX29(Chip8 *chip8, uint8_t x) {
    chip8->I = 0x50 + (chip8->V[x] * 5);
}
```

## FX33
This instruction takes the number in VX and converts it to 3 individual digits, then stores these three numbers at the address in the index register.

```C
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
```

## FX55 & FX65
FX55 stores the values from V0 to VX in successive memory addresses. starting with the one at the index register. While FX65 does the opposite, it stores the values at the memory address at the index register to the index register + X and stores them into the variable registers.

```C
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
```
