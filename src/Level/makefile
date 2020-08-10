CC = g++
CFLAGS = -c
DEBUG = -Wall -Werror -Wextra
THREAD = -pthread
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: game-sfml

debug: all

level1.o: level1.cpp level1.hpp ../Map/map.o ../Map/map1.txt ../Player/player.o ../Input/input.o
	$(CC) -shared $(CFLAGS) $(THREAD) map.o player.o input.o level1.cpp  $(SFML)

clean:
	\rm *.o game-sfml

run: all
run:
	./game-sfml