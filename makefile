CC = gcc
CFLAGS = -Wall -Wextra -O2
LIBS = $(shell pkg-config --cflags --libs sdl2 SDL2_image)

TARGET = imgv
SRC = main.c
ARG1 ?= think.png
ARG2 ?= -v

.PHONY: all build run clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

run: $(TARGET)
	./$(TARGET) $(ARG1) $(ARG2)

clean:
	rm -f $(TARGET)
