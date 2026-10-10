CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -std=c11

TARGET = mockFC

SRC = src/main.c

OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run:
	./mockFC