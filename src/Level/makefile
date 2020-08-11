CC = g++
CFLAGS = -c
DEBUG = -Wall -Werror -Wextra
THREAD = -pthread
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: level1.o

level1.o: level1.cpp level1.hpp ../Map/map.o ../Map/map1.txt ../Player/player.o ../Input/input.o
	$(CC) -shared $(CFLAGS) $(THREAD) level1.cpp  $(SFML)

clean:
	\rm *.o 