CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -O2 -Iinclude
TARGET  := flight_simulator
SRC     := src/main.c
HDR     := include/common.h

.PHONY: all run demo clean

all: $(TARGET)

$(TARGET): $(SRC) $(HDR)
	$(CC) $(CFLAGS) -o $@ $(SRC)

run: $(TARGET)
	./$(TARGET)

# Same simulation, fuel burns 8x faster so LOW FUEL / EMERGENCY appear within minutes.
demo: $(TARGET)
	./$(TARGET) --demo

clean:
	rm -f $(TARGET)
