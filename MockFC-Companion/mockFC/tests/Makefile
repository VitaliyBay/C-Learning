CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Werror -I../src

TARGET = test_clock

SRC = test_clock.c ../src/clock.c

OBJ = $(SRC:.c=.o)

all: run

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)