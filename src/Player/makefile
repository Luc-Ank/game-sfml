CC = g++
CFLAGS = -c
DEBUG = -Wall -Werror -Wextra
THREAD = -pthread
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: player.o

player.o: player.cpp player.hpp ../Input/input.o ../Monster/monster.o ../Map/map.o
	$(CC) -shared $(CFLAGS) $(THREAD)  player.cpp  $(SFML)

clean:
	\rm *.o 