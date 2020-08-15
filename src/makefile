CC = clang++
CFLAGS = -c
DEBUG = -Wall -Werror -Wextra
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: game-sfml map-editor

debug: DEBUG += -g -fsanitize=address
debug: all

game-sfml: test.o Level/level1.o 
	$(CC) test.o Map/map.o Level/level1.o Input/input.o Player/player.o Monster/monster.o Collision/collision.o -o game-sfml $(SFML)

test.o: test.cpp Level/level1.o 
	$(CC) $(CFLAGS) test.cpp

clean:
	rm *.o game-sfml

map-editor: map-editor.o map-editor-cls/Window.o Map/map.o
	$(CC) $(DEBUG) map-editor.o map-editor-cls/Window.o Map/map.o -o map-editor $(SFML)

map-editor.o: map-editor.cpp
	$(CC) $(DEBUG) $(CFLAGS) map-editor.cpp


run: all
run:
	./game-sfml
