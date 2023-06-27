CXX=g++
CC=$(CXX)

CFLAGS = -pedantic -Wall -Werror
CFLAGS += -g -O3
CXXFLAGS = $(CFLAGS) -std=c++17

CPPFLAGS = -DDEBUG
CPPFLAGS += -I$(INCLUDES_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

SOURCE = utest.cpp 
TARGET = utest

all: $(TARGET)

utest: $(SOURCE)

check : $(TARGET)
	# @./$(TARGET)
	@./$(TARGET) -v

vala: $(TARGET)
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET) 2> vala.txt

hell: $(TARGET)
	valgrind  --tool=helgrind ./$(TARGET) 2> hell.txt

recheck: clean check

clean:
	@$(RM) -f ./$(TARGET) *.o

.PHONY : make clean check recheck all

make:
	@echo 'Attend a maker faire'
	@${TRUE}
