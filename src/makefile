CC = g++
CFLAGS = -c
DEBUG = -Wall -Werror -Wextra
THREAD = -pthread
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: game-sfml level-editor

debug: all

game-sfml: test.o Level/level1.o 
	$(CC) $(THREAD) test.o Map/map.o Level/level1.o Input/input.o Player/player.o Monster/monster.o -o game-sfml $(SFML)

test.o: test.cpp Level/level1.o 
	$(CC) $(CFLAGS) $(THREAD) test.cpp $(SFML)

clean:
	\rm *.o game-sfml

level-editor: level-editor.o lvl-editor/levelWindow.o lvl-editor/tileWindow.o
	$(CC) $(THREAD) level-editor.o lvl-editor/levelWindow.o lvl-editor/tileWindow.o -o level-editor $(SFML)

level-editor.o: level-editor.cpp
	$(CC) $(THREAD) $(SFML) $(CFLAGS) level-editor.cpp


run: all
run:
	./game-sfml