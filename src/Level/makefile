CC = g++
CFLAGS = -c
DEBUG = -Wall -Werror -Wextra
THREAD = -pthread
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: level1.o

level1.o: level1.cpp level1.hpp ../Player/player.o ../Input/input.o ../Monster/monster.o ../Map/map.o
	$(CC) -shared $(CFLAGS) $(THREAD) level1.cpp  $(SFML)

clean:
	\rm *.o 