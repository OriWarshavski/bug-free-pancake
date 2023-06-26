CXX=g++
CC=$(CXX)

CFLAGS = -pedantic -Wall -Werror
CFLAGS += -g
CXXFLAGS = $(CFLAGS) -std=c++17

CPPFLAGS = -DDEBUG
CPPFLAGS = -I$(INCLUDES_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

SOURCE = utest.cpp $(SOURCES_DIR)/algos.cpp
TARGET = utest

all: $(TARGET)

utest: $(SOURCE)

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

texts: texts.zip
	unzip -o texts.zip

clean:
	@$(RM) -f ./$(TARGET) *.o


.PHONY : make clean check recheck all

make:
	@echo 'Attend a maker faire'
	@${TRUE}
