CC = g++
CFLAGS = -c
DEBUG = -Wall -Werror -Wextra
THREAD = -pthread
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: map.o

map.o: map.cpp map.hpp map1.txt
	$(CC) -shared $(CFLAGS) $(THREAD) map.cpp $(SFML)

clean:
	\rm *.o 

