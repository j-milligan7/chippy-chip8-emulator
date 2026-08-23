CC = clang
CFLAGS = -Wall -Wextra -std=c11

SDL_CFLAGS = -I/opt/homebrew/include
SDL_LIBS = -L/opt/homebrew/lib -lSDL2

SRC = src/main.c \
      src/chip8.c \
      src/instructions.c \
      src/display.c

OBJ = $(SRC:.c=.o)

chip8: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(SDL_LIBS) -o chip8

%.o: %.c
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) chip8
