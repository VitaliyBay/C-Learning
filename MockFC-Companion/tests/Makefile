CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Werror -I../common

TARGET = test_validations

SRC = test_validations.c ../common/validations.c

OBJ = $(SRC:.c=.o)

TARGET_ENCODING = test_encoding

SRC_ENCODING = test_encoding.c ../common/encoding.c

OBJ_ENCODING = $(SRC_ENCODING:.c=.o)

all: run

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) $(OBJ_ENCODING) $(TARGET_ENCODING)

run: $(TARGET)
	./$(TARGET)

$(TARGET_ENCODING): $(OBJ_ENCODING)
	$(CC) $(OBJ_ENCODING) -o $(TARGET_ENCODING)

encoding: $(TARGET_ENCODING)
	./$(TARGET_ENCODING) 