#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include "chip8.h"

int display_init(void);
void display_update(Chip8 *chip8);
void display_cleanup(void);
void display_handle_events(Chip8 *chip8, int *running);


#endif
