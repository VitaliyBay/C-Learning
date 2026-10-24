CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Werror -I../src

TARGET_SCENARIO = test_scenario

SRC_SCENARIO = test_scenario.c ../src/clock.c ../src/scenario.c ../src/sensors.c

OBJ_SCENARIO = $(SRC_SCENARIO:.c=.o)

TARGET = test_clock

SRC = test_clock.c test_scenario.c ../src/clock.c ../src/scenario.c ../src/sensors.c

OBJ = $(SRC:.c=.o)

all: run

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

$(TARGET_SCENARIO): $(OBJ_SCENARIO)
	$(CC) $(OBJ_SCENARIO) -o $(TARGET_SCENARIO)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) $(OBJ_SCENARIO) $(TARGET_SCENARIO)

run: $(TARGET)
	./$(TARGET)

scenario:  $(TARGET_SCENARIO)
			./$(TARGET_SCENARIO)