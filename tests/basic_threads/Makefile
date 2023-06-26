CXX=g++
CC=$(CXX)

CFLAGS = -pedantic -Wall -Werror
CFLAGS += -g -O3
CXXFLAGS = $(CFLAGS) -std=c++17

LDFLAGS = -L$(SFML)/lib
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SFML = /opt/homebrew/Cellar/sfml/2.5.1_2

CPPFLAGS = -DDEBUG
CPPFLAGS += -I$(SFML)/include
CPPFLAGS += -I$(INCLUDES_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

SOURCE = utest.cpp $(SOURCES_DIR)/basic_threads.cpp
TARGET = utest

all: $(TARGET)

utest: $(SOURCE)

check : $(TARGET)
	# @./$(TARGET)
	@./$(TARGET) -v
recheck: clean check

clean:
	@$(RM) -f ./$(TARGET) *.o *.jpeg

.PHONY : make clean check recheck all

make:
	@echo 'Attend a maker faire'
	@${TRUE}
