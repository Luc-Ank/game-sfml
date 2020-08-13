CC = g++
CFLAGS = -c
DEBUG = -Wall -Werror -Wextra
THREAD = -pthread
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: monster.o

monster.o: monster.cpp monster.hpp ../Map/map.o 
	$(CC) -shared $(CFLAGS) $(THREAD)  monster.cpp  $(SFML)

clean:
	\rm *.o 