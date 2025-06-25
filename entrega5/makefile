# Makefile for compiling lesson1.c with OpenGL

CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lGL -lGLU -lglut -lm

TARGET = lesson5
SRC = lesson5.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)