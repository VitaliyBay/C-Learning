CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Werror -I../src

TARGET_SCENARIO = test_scenario

SRC_SCENARIO = test_scenario.c ../src/clock.c ../src/scenario.c ../src/sensors.c

OBJ_SCENARIO = $(SRC_SCENARIO:.c=.o)

TARGET_CLOCK = test_clock

SRC_CLOCK = test_clock.c ../src/clock.c ../src/scenario.c ../src/sensors.c

OBJ_CLOCK = $(SRC_CLOCK:.c=.o)

all: clock scenario

$(TARGET_CLOCK): $(OBJ_CLOCK)
	$(CC) $(OBJ_CLOCK) -o $(TARGET_CLOCK)

$(TARGET_SCENARIO): $(OBJ_SCENARIO)
	$(CC) $(OBJ_SCENARIO) -o $(TARGET_SCENARIO)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_CLOCK) $(TARGET_CLOCK) $(OBJ_SCENARIO) $(TARGET_SCENARIO)

clock: $(TARGET_CLOCK)
	./$(TARGET_CLOCK)

scenario:  $(TARGET_SCENARIO)
			./$(TARGET_SCENARIO)