CC = g++
CFLAGS = -c
DEBUG = -Wall -Werror -Wextra
THREAD = -pthread
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: spell.o

spell.o: spell.cpp spell.hpp ../Input/input.o ../Monster/monster.o ../Map/map.o
	$(CC) -shared $(CFLAGS) $(THREAD)  spell.cpp  $(SFML)

clean:
	\rm *.o 