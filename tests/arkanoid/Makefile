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

OBJECTS = arkanoid.o $(SOURCES_DIR)/game_manager.o $(SOURCES_DIR)/ball.o $(SOURCES_DIR)/paddle.o 
OBJECTS += $(SOURCES_DIR)/collision.o $(SOURCES_DIR)/brick.o $(SOURCES_DIR)/bricksGroup.o
OBJECTS += $(SOURCES_DIR)/score.o $(SOURCES_DIR)/player.o $(SOURCES_DIR)/live.o
OBJECTS += $(SOURCES_DIR)/button.o $(SOURCES_DIR)/menu_screen.o 
OBJECTS += $(SOURCES_DIR)/top_ten_screen.o
OBJECTS += $(SOURCES_DIR)/input.o $(SOURCES_DIR)/clock.o
OBJECTS += $(SOURCES_DIR)/unbreackable_brick.o $(SOURCES_DIR)/sound_effect.o

TARGET = arkanoid

all: $(TARGET) audio

$(TARGET): $(OBJECTS) 

#	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE) $(LDLIBS) $(CPPFLAGS)

check : $(TARGET) audio
	@./$(TARGET) -v

recheck: clean check

audio: audio.zip
	if [ ! -d "audio" ]; then unzip -o audio.zip; fi

clean:
	@$(RM) -f ./$(TARGET) $(OBJECTS) *.dSYM *.json *.ttf
	@$(RM) -rf audio
# @$(RMDIR) -f __MACOSX

.PHONY : make clean check recheck all

arkanoid.o: arkanoid.cpp $(INCLUDES_DIR)/game_manager.hpp
game_manager.o: $(SOURCES_DIR)/game_manager.cpp $(INCLUDES_DIR)/game_manager.hpp