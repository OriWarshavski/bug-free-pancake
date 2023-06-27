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

OBJECTS = sound_test.o
OBJECTS += $(SOURCES_DIR)/sound_effect.o
TARGET = sound_test

all: $(TARGET)  ../arkanoid/audio

$(TARGET): $(OBJECTS) 

#	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE) $(LDLIBS) $(CPPFLAGS)

check : $(TARGET)  ../arkanoid/audio
	@./$(TARGET) -v

recheck: clean check

audio: ../arkanoid/audio.zip
	if [ ! -d "audio" ]; then unzip -o  ../arkanoid/audio.zip; fi

clean:
	@$(RM) -f ./$(TARGET) $(OBJECTS) *.dSYM *.json *.ttf
	@$(RM) -rf audio

.PHONY : make clean check recheck all
