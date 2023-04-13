CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -lm -o build/task main.c
OBJ_DIR=build
SRC_DIR=src
SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
EXEC=$(OBJ_DIR)/task

.PHONY: clean

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*


