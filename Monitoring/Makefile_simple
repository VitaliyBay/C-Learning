CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic

TARGET = drone_monitor

INCLUDE = -Iinclude/

SRC = src/main.c src/monitoring.c

$(TARGET): $(SRC)
	$(CC) $(INCLUDE) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

run:
	./drone_monitor