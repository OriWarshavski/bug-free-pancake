CC = gcc

CFLAGS = -ansi -pedantic -Wall -Werror -g -lpthread -I$(INCLUDES_DIR) -std=c99

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

SOURCE := counting_threads.c
TARGET = test

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) -o $(TARGET) $(SOURCE) $(CFLAGS)

check: $(TARGET)
	@./$(TARGET) -v

clean:
	@$(RM) -f ./$(TARGET) *.o