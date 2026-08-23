CC = clang
CFLAGS = -Wall -Wextra -g

TARGET = chip8

SRC = src/main.c \
      src/chip8.c \
      src/instructions.c \
      src/display.c

OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)
