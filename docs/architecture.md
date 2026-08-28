#Architecture

## Overview
Chippy (named after a dog i know) is a chip-8 emulator that is written in C. This emulator is split into multiple components with the Chip8 struct representing the state of the virtual machine and separate modules handling instruction execution and the display functionality.

The main components are:

- Chip8: Stores the state of the virtual machine.
- Instructions: Implements all of the original chip-8 instruction set.
- Display: Handles rendering using SDL2.
- Main: Initialises the emulator, loads ROMs, handles the main loop and connects the emulator to the display.

The architecture is very simple, as the chip-8 itself is a small virtual machine.

The Chip8 struct acts as the central state of the emulator. The instructions operate on this state and the display module uses the display state to produce graphical output.

## Chip8 State

The Chip8 struct:  
```C
struct Chip8 {
    uint8_t memory[4096];
    uint8_t V[16];
    uint16_t I;
    uint16_t PC;
    uint16_t stack[16];
    uint8_t SP;
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t display[64 * 32];
    bool keypad[16];
};
```

The Chip8 structure contains:  
- 4096 bytes of memory
- 16 general purpose registers
- Index register
- Program counter
- Stack
- Stack pointer
- Delay timer
- Sound timer
- Display buffer
- Keypad state

keeping all of these together allows an instruction to modify the virtual machine state through the one object.

## CPU Execution Cycle
The emulator performs a fetch-decode-execute cycle.

### 1.Fetch
Two bytes are read from memory at the location of the program counter, then the program counter increments and points towards the next instruction.  
```C
uint16_t fetch(Chip8 *chip8) {
    uint16_t opcode;
    opcode = ((uint16_t)chip8->memory[chip8->PC] << 8) | (chip8->memory[chip8->PC + 1]);
    chip8->PC += 2;
    return opcode;
}
```

### 2.Decode
The opcode that was fetched is then split into multiple components, I used an Instruction struct to keep them together and have them easily accessible.  
```C
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
```

### 3.Execute
The decoded instruction is then passed into the execute_instruction function, which is a huge switch statement. This then calls a function defined in instructions.c for the appropriate instruction. The instruction affects the Chip8 state directly.

### Instruction Dispatch
The Chip8 instruction set is implemented in instructions.c

The instruction "group" is determined by the first nibble. Some instruction groups will need further decoding of the lower nibbles.
