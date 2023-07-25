CC = gcc

CFLAGS = -ansi -pedantic -Wall -Werror -g -lpthread -I$(INCLUDES_DIR) -std=c99

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

SOURCE := pointers.c
TARGET = test

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) -o $(TARGET) $(SOURCE) $(CFLAGS)

check: $(TARGET)
	@./$(TARGET)

clean:
	@$(RM) -f ./$(TARGET) *.o