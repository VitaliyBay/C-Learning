CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -I../common -std=c11

TARGET = mockFC

SRC = src/main.c src/sensors.c

OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run:
	./mockFC