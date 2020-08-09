CC = g++
CFLAGS = -c
DEBUG = -Wall -Werror -Wextra
THREAD = -pthread
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: game-sfml

debug: all

map.o: map.cpp map.hpp
	$(CC) -shared $(CFLAGS) $(THREAD) map.cpp $(SFML)

clean:
	\rm *.o game-sfml

run: all
run:
	./game-sfml