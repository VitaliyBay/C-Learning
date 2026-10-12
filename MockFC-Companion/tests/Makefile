CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Werror -I../common

TARGET = test_validations

SRC = test_validations.c ../common/validations.c

OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run:
	./test_validations