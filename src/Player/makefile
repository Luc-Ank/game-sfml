CC = g++
CFLAGS = -c
DEBUG = -Wall -Werror -Wextra
THREAD = -pthread
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: game-sfml

debug: all

level1.o: player.cpp player.hpp ../Input/input.o
	$(CC) -shared $(CFLAGS) $(THREAD) input.o player.cpp  $(SFML)

clean:
	\rm *.o game-sfml

run: all
run:
	./game-sfml