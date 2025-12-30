CC = clang

SRC_DIR = src
OBJ_DIR = obj
EXT     = c

BASENAMES = main

SOURCES = $(addprefix $(SRC_DIR)/,$(addsuffix .$(EXT),$(BASENAMES)))
OBJECTS = $(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(BASENAMES)))

CFLAGS = -Wall -Wextra -Wpedantic -std=c23 -O0 -g

TARGET = project

launch: all run

run:
	@./$(TARGET)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@


clean:
	@rm -rf $(OBJ_DIR)
	@rm ./$(TARGET)