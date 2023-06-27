CXX=clang++
CC= $(CXX)
CFLAGS = -pedantic -Wall -Werror
CFLAGS += -g
CXXFLAGS = $(CFLAGS) -std=c++17

#LD = linker
LDFLAGS = -L$(SFML)/lib
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SFML = /opt/homebrew/Cellar/sfml/2.5.1_2
CPPFLAGS = -DDEBUG
CPPFLAGS += -I$(SFML)/include
CPPFLAGS += -I$(INCLUDES_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

OBJECTS = score_table.o
OBJECTS += $(SOURCES_DIR)/top_ten_screen.o
TARGET = score_table

all: $(TARGET)

$(TARGET): $(OBJECTS)

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

clean:
	@$(RM) -f ./$(TARGET) $(OBJECTS) *.dSYM *.json *.ttf
# @$(RMDIR) -f __MACOSX

.PHONY : make clean check recheck all
