#include "display.h"
#include "chip8.h"

static SDL_Window *window;
static SDL_Renderer *renderer;

int display_init(void) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0)) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 0;
    }

    window = SDL_CreateWindow(
        "CHIP-8 EMULATOR",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        320,
        SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (renderer == NULL) {
        printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
    }
    return 1;
}

void display_update(Chip8 *chip8) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int y = 0; y < 32; y++) {
        for (int x = 0; x < 64; x++) {

            if (chip8->display[y * 64 + x]) {
                SDL_Rect pixel = {
                    x * 10,
                    y * 10,
                    10,
                    10
                };

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &pixel);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void display_handle_events(Chip8 *chip8, int *running) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_QUIT) {
            *running = 0;
        }

        if (event.type == SDL_KEYDOWN) {

            switch (event.key.keysym.sym) {

                case SDLK_1:
                    chip8->keypad[0x1] = 1;
                    break;

                case SDLK_2:
                    chip8->keypad[0x2] = 1;
                    break;

                case SDLK_3:
                    chip8->keypad[0x3] = 1;
                    break;

                case SDLK_4:
                    chip8->keypad[0xC] = 1;
                    break;

                case SDLK_q:
                    chip8->keypad[0x4] = 1;
                    break;

                case SDLK_w:
                    chip8->keypad[0x5] = 1;
                    break;

                case SDLK_e:
                    chip8->keypad[0x6] = 1;
                    break;

                case SDLK_r:
                    chip8->keypad[0xD] = 1;
                    break;

                case SDLK_a:
                    chip8->keypad[0x7] = 1;
                    break;

                case SDLK_s:
                    chip8->keypad[0x8] = 1;
                    break;

                case SDLK_d:
                    chip8->keypad[0x9] = 1;
                    break;

                case SDLK_f:
                    chip8->keypad[0xE] = 1;
                    break;

                case SDLK_z:
                    chip8->keypad[0xA] = 1;
                    break;

                case SDLK_x:
                    chip8->keypad[0x0] = 1;
                    break;

                case SDLK_c:
                    chip8->keypad[0xB] = 1;
                    break;

                case SDLK_v:
                    chip8->keypad[0xF] = 1;
                    break;
            }
        }

        if (event.type == SDL_KEYUP) {

            switch (event.key.keysym.sym) {

                case SDLK_1: chip8->keypad[0x1] = 0; break;
                case SDLK_2: chip8->keypad[0x2] = 0; break;
                case SDLK_3: chip8->keypad[0x3] = 0; break;
                case SDLK_4: chip8->keypad[0xC] = 0; break;

                case SDLK_q: chip8->keypad[0x4] = 0; break;
                case SDLK_w: chip8->keypad[0x5] = 0; break;
                case SDLK_e: chip8->keypad[0x6] = 0; break;
                case SDLK_r: chip8->keypad[0xD] = 0; break;

                case SDLK_a: chip8->keypad[0x7] = 0; break;
                case SDLK_s: chip8->keypad[0x8] = 0; break;
                case SDLK_d: chip8->keypad[0x9] = 0; break;
                case SDLK_f: chip8->keypad[0xE] = 0; break;

                case SDLK_z: chip8->keypad[0xA] = 0; break;
                case SDLK_x: chip8->keypad[0x0] = 0; break;
                case SDLK_c: chip8->keypad[0xB] = 0; break;
                case SDLK_v: chip8->keypad[0xF] = 0; break;
            }
        }
    }
}

void display_cleanup(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
