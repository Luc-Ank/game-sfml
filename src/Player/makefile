CC = g++
CFLAGS = -c
DEBUG = -Wall -Werror -Wextra
THREAD = -pthread
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: level1.o

level1.o: player.cpp player.hpp ../Input/input.o
	$(CC) -shared $(CFLAGS) $(THREAD)  player.cpp  $(SFML)

clean:
	\rm *.o 