CC = gcc
CFLAGS = -Wall -Wextra -O2
LIBS = $(shell pkg-config --cflags --libs sdl2 SDL2_image)

TARGET = imgv
SRC = main.c
ARGS ?= think.png

.PHONY: all build run clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

run: $(TARGET)
	./$(TARGET) $(ARGS)

clean:
	rm -f $(TARGET)
