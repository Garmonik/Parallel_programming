CC = mpicc
CFLAGS = -Wall
LDFLAGS = -lm

SRC = main.c
OBJ = $(SRC:.c=.o)

EXEC = build/task

all: $(EXEC)

$(EXEC): $(OBJ)
	mkdir -p build
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf build

