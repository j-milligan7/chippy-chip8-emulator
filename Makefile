CC ?= gcc

CFLAGS := -Wall -Wextra -std=c11
SDL_CFLAGS := $(shell pkg-config --cflags sdl2)
SDL_LIBS := $(shell pkg-config --libs sdl2)

SRC_DIR := src
BUILD_DIR := build
TEST_DIR := tests
TEST_BUILD_DIR := testBuild

TARGET := chip8
TEST_TARGET := test_runner

SRC := $(wildcard $(SRC_DIR)/*.c)
CORE_SRC := $(filter-out $(SRC_DIR)/main.c,$(SRC))
OBJ := $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

TEST_SRC := $(wildcard $(TEST_DIR)/*.c)
CORE_TEST_OBJ := $(CORE_SRC:$(SRC_DIR)/%.c=$(TEST_BUILD_DIR)/%.o)
TEST_OBJ := $(TEST_SRC:$(TEST_DIR)/%.c=$(TEST_BUILD_DIR)/%.o)

.PHONY: all test debug clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ $(SDL_LIBS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c $< -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(CORE_TEST_OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) $^ $(SDL_LIBS) -o $@

$(TEST_BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(TEST_BUILD_DIR)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -I$(SRC_DIR) -c $< -o $@

$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	mkdir -p $(TEST_BUILD_DIR)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -I$(SRC_DIR) -c $< -o $@

debug: CFLAGS += -g -O0
debug: clean all

clean:
	rm -rf $(BUILD_DIR) $(TEST_BUILD_DIR) $(TARGET) $(TEST_TARGET)
