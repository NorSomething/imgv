CC = gcc
CFLAGS = -Wall -Wextra -O2
LIBS = $(shell pkg-config --cflags --libs sdl2 SDL2_image)

TARGET = imgv
SRC = main.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)
