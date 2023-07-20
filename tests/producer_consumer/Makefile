CXX = gcc
# CC = $(CXX)

CFLAGS = -pedantic -Wall -Werror
CFLAGS += -g -lpthread -I$(INCLUDES_DIR)
# CXXFLAGS = $(CFLAGS) -std=c++20 -lpthread

# CPPFLAGS = -DDEBUG
# CPPFLAGS += -I$(INCLUDES_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

SOURCE := utest.c $(SOURCES_DIR)/producer_consumer.c
TARGET = utest

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) -o $(TARGET) $(SOURCE) $(CFLAGS)
# $(CC) $(CXXFLAGS) $(CPPFLAGS) -o $(TARGET) $(SOURCE)

check: $(TARGET)
	@./$(TARGET) -v

vala: $(TARGET)
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET) 2> vala.txt

hell: $(TARGET)
	valgrind --tool=helgrind ./$(TARGET) 2> hell.txt

recheck: clean check

clean:
	@$(RM) -f ./$(TARGET) *.o

.PHONY: clean check recheck all
